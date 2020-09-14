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
   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
   long long int time=10000000;
   double start,end,down,temp,up;
   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   start =clock();
   int i;
   for(i=1;i<=time;i++)
   {
   	serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(19);//�U��
   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   n=recv(sd, str_r, MAXLINE, 0); //��echo server����
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
   serv.sin_port         = htons(9);//�W��
   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   send(sd, str, strlen(str)+1, 0); //�ǰehow are you��echo server
   //printf("send: %s (%d bytes)\n" ,str,strlen(str)+1);

   }
   end=clock();
   temp=end-start;
   up=time/(temp)*1024/1000;
	printf("upload: %f bytes\n",up);


   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}
