CC = g++
DEBUGFLAG = -g
CFLAG = -Wall 
LFLAG = -I /usr/include -lpcap
RM = rm -f
TARGET = test_pcap

test_pcap: $(TARGET).cpp
	$(CC) $(CFLAG) $(LFLAG) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)

