#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fstream>
#include<stdio.h>
#include<iomanip>
#define MAXHOSTNAME 256
using namespace std;

int main(){
	struct sockaddr_in remoteSocketInfo;
	struct hostent *hostPtr;
	int socketHandle;
	const char *remoteHost = "localhost";
	int portNumber = 12345;
	
	//clear structure memory
	bzero(&remoteSocketInfo, sizeof(sockaddr_in));

	//get system info
	if((hostPtr = gethostbyname(remoteHost)) == NULL){
		cerr<<"System DNS name resolution not configured properly"<<endl;
		cerr<<"Error Number: "<<ECONNREFUSED<<endl;
		exit(EXIT_FAILURE);
	}

	//create tcp socket
	if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		close(socketHandle);
		exit(EXIT_FAILURE);
	}

	//load system info
	memcpy((char *)&remoteSocketInfo.sin_addr, hostPtr -> h_addr, hostPtr -> h_length);
	remoteSocketInfo.sin_family = AF_INET; //ipv4
	remoteSocketInfo.sin_port = htons((u_short)portNumber); //set port number

	if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0){
		close(socketHandle);
		exit(EXIT_FAILURE);
	}
		
	char buf[512];

	ifstream fin("a.pcap", ios::in|ios::binary);
	char ch;
	while(!fin.eof()){
		ch = fin.get();
		buf[0] = ch;
		cout<<buf;
		send(socketHandle, buf, strlen(buf) + 1, 0);
	}
	fin.close();
	close(socketHandle);
	return 0;
}

