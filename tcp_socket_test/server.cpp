#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<iomanip>
#define MAXHOSTNAME 256
using namespace std;

int main(){
	struct sockaddr_in SocketInfo;
	struct hostent *hostPtr;
	int socketHandle;
	char sysHost[MAXHOSTNAME + 1]; // hostname of the computer we are running on
	int portNumber = 12345;
	
	//clear structure memory
	bzero(&SocketInfo, sizeof(sockaddr_in));

	//get system info
	gethostname(sysHost, MAXHOSTNAME); //get the name of this computer we are running on
	if((hostPtr = gethostbyname(sysHost)) == NULL){
		cerr << "System hostname misconfigured. "<<endl;
		exit(EXIT_FAILURE);
	}

	//create socket
	if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		close(socketHandle);
		exit(EXIT_FAILURE);
	}

	//load the system info into socket data stucture
	SocketInfo.sin_family = AF_INET;
	SocketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
	SocketInfo.sin_port = htons(portNumber);

	//Bind the socket to a local socket address
	if(bind(socketHandle, (struct sockaddr *) &SocketInfo, sizeof(SocketInfo)) < 0){
		close(socketHandle);
		perror("bind");
		exit(EXIT_FAILURE);
	}

	listen(socketHandle, 1);
	int socketConnection;
	if((socketConnection = accept(socketHandle, NULL, NULL)) < 0){
		exit(EXIT_FAILURE);
	}
	close(socketHandle);

	int rc = 0;
	char buf[512];
	
	//rc = recv(socketConnection, buf, 512, 0);
	while( (rc = recv(socketConnection, buf, 512, 0)) != NULL){
	//while(rc){
		buf[rc] = (char)NULL; //NULL terminate string
		string str(buf);
		cout<<"Number of bytes read: "<<rc<<endl;
		cout<<"Received: ";

		for(int j = 0; j < rc; j++){
			cout<<buf[j];
			//cout<<hex<<setfill('0')<<buf[j] - '0';
		}
		cout<<endl;
		//rc = recv(socketConnection, buf, 512, 0);
	}

	return 0;
}

