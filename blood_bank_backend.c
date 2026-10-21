/* Web-connected integration backend for Smart Blood Bank Management System.
   The original classroom C file is kept separate and unchanged. This version
   exposes a line-based protocol to the local Python HTTP bridge. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DONORS 100
#define MAX_REQUESTS 100
#define QUEUE_SIZE 20
#define BLOOD_GROUPS 8
#define LINE_SIZE 512
struct Donor { int id; char name[50]; int age; char phone[20]; int bloodGroup; int totalDonations; int lastDay,lastMonth,lastYear,hasDonated; };
struct Request { int id; char hospital[60]; int bloodGroup; int units; int status; };
struct Transaction { int id; int bloodGroup; int units; int type; };
static const char *bloodNames[BLOOD_GROUPS] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
static struct Donor donors[MAX_DONORS];
static struct Request requests[MAX_REQUESTS];
static struct Transaction queue[QUEUE_SIZE];
static int stock[BLOOD_GROUPS] = {10,5,8,4,6,3,12,5};
static int donorCount=0,requestCount=0,front=0,rear=-1,queueCount=0;
static int nextDonorId=1001,nextRequestId=5001,nextTransactionId=1;
static char message[240] = "Backend ready. Demo stock is fictional classroom data.";
static int lastOk=1;

static void json_string(const char *s) { putchar('"'); for (; *s; s++) { unsigned char c=(unsigned char)*s; if(c=='"'||c=='\\') { putchar('\\'); putchar(c); } else if(c=='\n') fputs("\\n",stdout); else if(c=='\r') fputs("\\r",stdout); else if(c<32) fputc(' ',stdout); else putchar(c); } putchar('"'); }
static void copy_field(char *dst, size_t cap, const char *src) { if(!src) src=""; snprintf(dst,cap,"%s",src); }
static void reset_state(void) { memset(donors,0,sizeof(donors)); memset(requests,0,sizeof(requests)); memset(queue,0,sizeof(queue)); int initial[BLOOD_GROUPS]={10,5,8,4,6,3,12,5}; memcpy(stock,initial,sizeof(stock)); donorCount=0; requestCount=0; front=0; rear=-1; queueCount=0; nextDonorId=1001; nextRequestId=5001; nextTransactionId=1; }
static int days_in_month(int m,int y) { if(m==2) return ((y%400==0)||(y%4==0&&y%100!=0))?29:28; if(m==4||m==6||m==9||m==11)return 30; return 31; }
static long day_number(int d,int m,int y) { long n=0; int i; for(i=1;i<y;i++) n+=365+((i%400==0)||(i%4==0&&i%100!=0)); for(i=1;i<m;i++)n+=days_in_month(i,y); return n+d; }
static void output_state(void) {
 int i; printf("{\"ok\":%s,\"message\":",lastOk?"true":"false"); json_string(message); printf(",\"stock\":[");
 for(i=0;i<BLOOD_GROUPS;i++){if(i)putchar(',');printf("{\"group\":");json_string(bloodNames[i]);printf(",\"units\":%d}",stock[i]);} printf("],\"donors\":[");
 for(i=0;i<donorCount;i++){if(i)putchar(',');printf("{\"id\":%d,\"name\":",donors[i].id);json_string(donors[i].name);printf(",\"age\":%d,\"phone\":",donors[i].age);json_string(donors[i].phone);printf(",\"bloodGroup\":");json_string(bloodNames[donors[i].bloodGroup]);printf(",\"totalDonations\":%d,\"lastDonation\":",donors[i].totalDonations);if(donors[i].hasDonated){char date[20];snprintf(date,sizeof(date),"%02d-%02d-%04d",donors[i].lastDay,donors[i].lastMonth,donors[i].lastYear);json_string(date);}else json_string("Not recorded");putchar('}');} printf("],\"queue\":[");
 for(i=0;i<queueCount;i++){int p=(front+i)%QUEUE_SIZE;if(i)putchar(',');printf("{\"id\":%d,\"type\":",queue[p].id);json_string(queue[p].type==1?"ADD":"ISSUE");printf(",\"bloodGroup\":");json_string(bloodNames[queue[p].bloodGroup]);printf(",\"units\":%d}",queue[p].units);} printf("],\"requests\":[");
 for(i=0;i<requestCount;i++){if(i)putchar(',');printf("{\"id\":%d,\"hospital\":",requests[i].id);json_string(requests[i].hospital);printf(",\"bloodGroup\":");json_string(bloodNames[requests[i].bloodGroup]);printf(",\"units\":%d,\"status\":",requests[i].units);json_string(requests[i].status?"FULFILLED":"PENDING");putchar('}');} printf("],\"counts\":{\"donors\":%d,\"requests\":%d,\"queue\":%d,\"front\":%d,\"rear\":%d,\"nextDonorId\":%d}}\n",donorCount,requestCount,queueCount,front,rear,nextDonorId); fflush(stdout);
}
static void process_line(char *line) {
 char *cmd=strtok(line,"\t\r\n"), *a[6]={0}; int i; for(i=0;i<6;i++)a[i]=strtok(NULL,"\t\r\n"); lastOk=1; copy_field(message,sizeof(message),"State refreshed."); if(!cmd){lastOk=0;copy_field(message,sizeof(message),"Empty command.");return;}
 if(!strcmp(cmd,"GET")){copy_field(message,sizeof(message),"Live state read from the C backend.");}
 else if(!strcmp(cmd,"RESET")){reset_state();copy_field(message,sizeof(message),"C backend reset to initial demo stock.");}
 else if(!strcmp(cmd,"DONOR_ADD")){int age=atoi(a[1]?a[1]:"0"),g=atoi(a[2]?a[2]:"-1"); if(donorCount>=MAX_DONORS){lastOk=0;copy_field(message,sizeof(message),"Donor storage is full.");}else if(!a[0]||!*a[0]||age<18||age>100||g<0||g>=8){lastOk=0;copy_field(message,sizeof(message),"Enter a name, age 18-100, and a valid blood group.");}else{struct Donor *d=&donors[donorCount++];memset(d,0,sizeof(*d));d->id=nextDonorId++;copy_field(d->name,sizeof(d->name),a[0]);d->age=age;copy_field(d->phone,sizeof(d->phone),a[3]);d->bloodGroup=g;snprintf(message,sizeof(message),"Donor registered. ID %d.",d->id);}}
 else if(!strcmp(cmd,"DONATION")){int id=atoi(a[0]?a[0]:"0"),d=atoi(a[1]?a[1]:"0"),m=atoi(a[2]?a[2]:"0"),y=atoi(a[3]?a[3]:"0"),idx=-1;long now,prev;for(i=0;i<donorCount;i++)if(donors[i].id==id)idx=i;if(idx<0){lastOk=0;copy_field(message,sizeof(message),"Donor ID not found.");}else if(y<1900||y>2200||m<1||m>12||d<1||d>days_in_month(m,y)){lastOk=0;copy_field(message,sizeof(message),"Invalid calendar date.");}else{now=day_number(d,m,y);prev=donors[idx].hasDonated?day_number(donors[idx].lastDay,donors[idx].lastMonth,donors[idx].lastYear):0;if(donors[idx].hasDonated&&now<=prev){lastOk=0;copy_field(message,sizeof(message),"Donation date must be later than the previous date.");}else if(donors[idx].hasDonated&&now-prev<90){lastOk=0;copy_field(message,sizeof(message),"Donation not recorded: fewer than 90 days since last recorded donation. Classroom rule only.");}else{donors[idx].hasDonated=1;donors[idx].lastDay=d;donors[idx].lastMonth=m;donors[idx].lastYear=y;donors[idx].totalDonations++;copy_field(message,sizeof(message),"Donation history recorded. This is not a medical eligibility decision.");}}}
 else if(!strcmp(cmd,"STOCK_ADD")||!strcmp(cmd,"STOCK_ISSUE")){int g=atoi(a[0]?a[0]:"-1"),u=atoi(a[1]?a[1]:"0"),type=!strcmp(cmd,"STOCK_ADD")?1:2;if(queueCount>=QUEUE_SIZE){lastOk=0;copy_field(message,sizeof(message),"Circular transaction queue is full.");}else if(g<0||g>=8||u<=0){lastOk=0;copy_field(message,sizeof(message),"Choose a valid blood group and positive units.");}else if(type==2&&stock[g]<u){lastOk=0;copy_field(message,sizeof(message),"Insufficient stock for this issue.");}else{rear=(rear+1)%QUEUE_SIZE;queue[rear].id=nextTransactionId++;queue[rear].bloodGroup=g;queue[rear].units=u;queue[rear].type=type;queueCount++;stock[g]+=(type==1?u:-u);snprintf(message,sizeof(message),"%s transaction #%d enqueued; stock updated.",type==1?"ADD":"ISSUE",queue[rear].id);}}
 else if(!strcmp(cmd,"PROCESS")){if(!queueCount){lastOk=0;copy_field(message,sizeof(message),"No pending transactions.");}else{snprintf(message,sizeof(message),"Processed transaction #%d (%s). Stock was already updated at enqueue.",queue[front].id,queue[front].type==1?"ADD":"ISSUE");front=(front+1)%QUEUE_SIZE;queueCount--;if(!queueCount)rear=(front+QUEUE_SIZE-1)%QUEUE_SIZE;}}
 else if(!strcmp(cmd,"REQUEST_ADD")){int g=atoi(a[1]?a[1]:"-1"),u=atoi(a[2]?a[2]:"0");if(requestCount>=MAX_REQUESTS){lastOk=0;copy_field(message,sizeof(message),"Hospital request storage is full.");}else if(!a[0]||!*a[0]||g<0||g>=8||u<=0){lastOk=0;copy_field(message,sizeof(message),"Enter hospital, valid blood group, and positive units.");}else{struct Request *r=&requests[requestCount++];r->id=nextRequestId++;copy_field(r->hospital,sizeof(r->hospital),a[0]);r->bloodGroup=g;r->units=u;r->status=0;snprintf(message,sizeof(message),"Hospital request #%d saved.",r->id);}}
 else if(!strcmp(cmd,"FULFILL")){int id=atoi(a[0]?a[0]:"0"),idx=-1;for(i=0;i<requestCount;i++)if(requests[i].id==id)idx=i;if(idx<0){lastOk=0;copy_field(message,sizeof(message),"Request ID not found.");}else if(requests[idx].status){lastOk=0;copy_field(message,sizeof(message),"Request already fulfilled.");}else{int g=requests[idx].bloodGroup,u=requests[idx].units;if(stock[g]<u){lastOk=0;copy_field(message,sizeof(message),"Insufficient stock; request remains pending.");}else if(queueCount>=QUEUE_SIZE){lastOk=0;copy_field(message,sizeof(message),"Queue full; process transactions first.");}else{rear=(rear+1)%QUEUE_SIZE;queue[rear].id=nextTransactionId++;queue[rear].bloodGroup=g;queue[rear].units=u;queue[rear].type=2;queueCount++;stock[g]-=u;requests[idx].status=1;snprintf(message,sizeof(message),"Request #%d fulfilled; ISSUE transaction #%d enqueued.",id,queue[rear].id);}}}
 else if(!strcmp(cmd,"DEMO")){reset_state();donors[0]=(struct Donor){1001,"Aarav Kumar",24,"9000000001",0,1,1,1,2026,1};donors[1]=(struct Donor){1002,"Meera Nair",29,"9000000002",6,0,0,0,0,0};donors[2]=(struct Donor){1003,"Kiran Das",32,"9000000003",2,2,10,2,2026,1};donorCount=3;rear=0;queue[0]=(struct Transaction){1,0,2,1};queueCount=1;stock[0]+=2;nextTransactionId=2;requests[0]=(struct Request){5001,"City General Hospital",0,2,0};requests[1]=(struct Request){5002,"Community Care Hospital",6,1,0};requestCount=2;nextRequestId=5003;copy_field(message,sizeof(message),"Demo records loaded into C memory. Demo people and stock are fictional.");}
 else {lastOk=0;copy_field(message,sizeof(message),"Unknown command.");}
}
int main(void){char line[LINE_SIZE];reset_state();while(fgets(line,sizeof(line),stdin)){process_line(line);output_state();}return 0;}
