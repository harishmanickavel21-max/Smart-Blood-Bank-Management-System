# Smart Blood Bank Management System — Web + C integration

## How it works
- `blood_bank_backend.c` is the persistent C process and owns the stock, donors, queue, and hospital-request arrays in RAM.
- `server.py` is a small Python 3 HTTP bridge using only the Python standard library. It sends commands to that C process.
- `index.html`, `styles.css`, and `app.js` are the dashboard. Buttons call `/api/action`; state is re-read from the C process.
- The original classroom C source is not overwritten. This integration backend is a separate file because the interactive `scanf()` menu cannot also serve browser requests directly.

## Windows laptop
1. Put this folder on your laptop.
2. Install Python 3 and a C compiler (`gcc`, e.g. MinGW-w64/MSYS2). Ensure both are on PATH.
3. Double-click `start_windows.bat`.
4. Open `http://127.0.0.1:8000` in your browser.

## Linux/macOS laptop
1. Ensure Python 3 and a C compiler are installed.
2. In a terminal, enter this folder and run `./start_linux_mac.sh`.
3. Open `http://127.0.0.1:8000`.

## Android phone
Recommended: run the backend on a laptop, then open it on Android while both devices use the same trusted Wi-Fi.
1. Start the server on the laptop.
2. Find the laptop's LAN IPv4 address (`ipconfig` on Windows; `ip addr` on Linux; Network settings on macOS).
3. On Android Chrome, open `http://LAPTOP-IP:8000` (replace `LAPTOP-IP`, e.g. `192.168.1.20`). Allow Python through the laptop firewall on private networks if prompted. Do not use a public Wi-Fi network.

To run directly on Android, use a terminal app such as Termux, install Python and clang, compile `blood_bank_backend.c` with `clang -std=c11 -O2 blood_bank_backend.c -o blood_bank_backend`, then run `python server.py` in the same folder. Copy the whole project folder to the phone first. Depending on Android version and app restrictions, keeping the local server alive in the background may require keeping Termux open.

## Test flow
1. Click **Load Demo** to load fictional sample records in C memory.
2. Add a donor and refresh; it should appear in the donor table.
3. Enqueue an ADD or ISSUE transaction; stock changes and the transaction appears in the FIFO queue.
4. Click **Dequeue next**; the queue shrinks, but stock is not changed a second time.
5. Create a hospital request, then click **Fulfil**. It only succeeds if there is enough stock and queue space.
6. Click **Reset** to restore initial stock `{10, 5, 8, 4, 6, 3, 12, 5}` and clear records.

## Important limitations
- Data is in RAM and is cleared when the server/backend restarts. Persistence to a file/database is not included yet.
- This is an educational prototype using fictional demo stock. Do not use it for real patient care or operational blood-bank decisions. Donor interval logic is only a classroom rule; qualified staff must determine actual eligibility.
- The page uses Tailwind, Font Awesome, and Google Fonts CDNs, so those visual assets need internet access; the core dashboard/backend connection runs locally.
- Bind address is `0.0.0.0` so a phone on the same Wi-Fi can connect. Use only a trusted private network; this prototype has no login/authentication and must not be exposed to the public internet.
