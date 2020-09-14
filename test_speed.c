#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]="abc";
   char  		str_r[1024];
   WSADATA 		wsadata;
   int n,td,tu;
   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   long long int time=10000000;
   double start,end,down,temp,up;
   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   //為連線作準備，包含填寫 sockaddr_in 結構 (serv) 。
   //內容有：server 的 IP 位址，port number 等等。
   start =clock();
   int i;
   for(i=1;i<=time;i++)
   {
   	serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(19);//下載
   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   n=recv(sd, str_r, MAXLINE, 0); //由echo server接收
   //printf("recv: %s (%d bytes)\n",str_r,n);
   }
   end=clock();
   temp=end-start;
   down=time/temp*1024/1000;
   printf("dowload: %f bytes\n",down);
   for(i=0;i<1024;i++)
   {
   	str[i]='a';
   }
   start=clock();

   for(i=1;i<=time;i++)
   {
   	serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(9);//上傳
   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   send(sd, str, strlen(str)+1, 0); //傳送how are you至echo server
   //printf("send: %s (%d bytes)\n" ,str,strlen(str)+1);

   }
   end=clock();
   temp=end-start;
   up=time/(temp)*1024/1000;
	printf("upload: %f bytes\n",up);


   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用
   system("pause");

   return 0;
}
