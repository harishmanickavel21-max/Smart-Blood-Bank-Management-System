#!/usr/bin/env python3
"""Local HTTP bridge: browser <-> Python HTTP <-> persistent C backend process."""
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler
from pathlib import Path
import json, os, subprocess, threading, urllib.parse
ROOT = Path(__file__).resolve().parent
HOST = os.environ.get('BB_HOST', '0.0.0.0')
PORT = int(os.environ.get('BB_PORT', '8000'))
lock = threading.Lock()
proc = None

def start_backend():
    global proc
    exe = ROOT / ('blood_bank_backend.exe' if os.name == 'nt' else 'blood_bank_backend')
    if not exe.exists():
        raise RuntimeError('C backend not compiled. Run start_windows.bat or ./start_linux_mac.sh first.')
    proc = subprocess.Popen([str(exe)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, bufsize=1, cwd=ROOT)

def command(line):
    with lock:
        if proc is None or proc.poll() is not None:
            raise RuntimeError('C backend process is not running. Restart the server.')
        proc.stdin.write(line.replace('\r',' ').replace('\n',' ') + '\n')
        proc.stdin.flush()
        response = proc.stdout.readline()
        if not response:
            raise RuntimeError('C backend stopped without a response.')
        return json.loads(response)

class Handler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(ROOT), **kwargs)
    def log_message(self, fmt, *args):
        print('[web]', fmt % args)
    def send_json(self, obj, status=200):
        body=json.dumps(obj).encode()
        self.send_response(status); self.send_header('Content-Type','application/json; charset=utf-8'); self.send_header('Content-Length',str(len(body))); self.send_header('Cache-Control','no-store'); self.send_header('Access-Control-Allow-Origin','*'); self.end_headers(); self.wfile.write(body)
    def do_OPTIONS(self):
        self.send_response(204); self.send_header('Access-Control-Allow-Origin','*'); self.send_header('Access-Control-Allow-Methods','GET, POST, OPTIONS'); self.send_header('Access-Control-Allow-Headers','Content-Type'); self.end_headers()
    def do_GET(self):
        if self.path.startswith('/api/state'):
            try: self.send_json(command('GET'))
            except Exception as e: self.send_json({'ok':False,'message':str(e)},500)
        else: super().do_GET()
    def do_POST(self):
        if not self.path.startswith('/api/action'):
            self.send_json({'ok':False,'message':'Unknown endpoint.'},404); return
        try:
            size=int(self.headers.get('Content-Length','0'))
            if size > 10000: raise ValueError('Request body too large.')
            data=json.loads(self.rfile.read(size) or b'{}')
            action=data.get('action','')
            if action=='reset': line='RESET'
            elif action=='demo': line='DEMO'
            elif action=='process': line='PROCESS'
            elif action=='donor_add':
                name=str(data.get('name','')).strip()[:49]; phone=str(data.get('phone','')).strip()[:19]
                if any(c in name+phone for c in '\t\r\n'): raise ValueError('Tabs/newlines are not allowed.')
                line='DONOR_ADD\t{}\t{}\t{}\t{}'.format(name,int(data.get('age',0)),int(data.get('group',-1)),phone)
            elif action=='donation': line='DONATION\t{}\t{}\t{}\t{}'.format(int(data.get('id',0)),int(data.get('day',0)),int(data.get('month',0)),int(data.get('year',0)))
            elif action in ('stock_add','stock_issue'): line=('STOCK_ADD' if action=='stock_add' else 'STOCK_ISSUE')+'\t{}\t{}'.format(int(data.get('group',-1)),int(data.get('units',0)))
            elif action=='request_add':
                hospital=str(data.get('hospital','')).strip()[:59]
                if any(c in hospital for c in '\t\r\n'): raise ValueError('Tabs/newlines are not allowed.')
                line='REQUEST_ADD\t{}\t{}\t{}'.format(hospital,int(data.get('group',-1)),int(data.get('units',0)))
            elif action=='fulfill': line='FULFILL\t{}'.format(int(data.get('id',0)))
            else: self.send_json({'ok':False,'message':'Unknown action.'},400); return
            self.send_json(command(line))
        except Exception as e: self.send_json({'ok':False,'message':str(e)},400)

if __name__=='__main__':
    start_backend()
    print('Smart Blood Bank running: http://127.0.0.1:%d' % PORT)
    print('For phone on same Wi-Fi, open this computer IP at port %d.' % PORT)
    try: ThreadingHTTPServer((HOST,PORT),Handler).serve_forever()
    except KeyboardInterrupt: print('\nServer stopped.')
    finally:
        if proc and proc.poll() is None: proc.terminate()
