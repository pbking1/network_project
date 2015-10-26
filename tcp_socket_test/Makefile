CC = g++
DEBUGFLAG = -g
CFLAG = -Wall 
LFLAG = -I /usr/include -lpcap
RM = rm -f

target:
	$(CC) $(CFLAG) $(LFLAG) -o client client.cpp
	$(CC) $(CFLAG) $(LFLAG) -o server server.cpp

clean:
	$(RM) server && ${RM} client

