/*
 *sample code can be read from devdungeon.com/content/using-libpcap-c
 *
 */
#include<pcap.h>
#include<iostream>
#include<string>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<net/ethernet.h>
#include<net/if.h>
#include<netinet/if_ether.h>
#include<iomanip>

using namespace std;

int main(){
	string filename = "./sample.pcapng";	
	char error_buffer[PCAP_ERRBUF_SIZE];

	struct pcap_pkthdr header;

	pcap_t *handle  = pcap_open_offline_with_tstamp_precision(filename.c_str(), PCAP_TSTAMP_PRECISION_NANO, error_buffer);
	
	//filter
	char filter_str[] = "dst host 23.210.50.54";
	//char filter_str[] = "port 23";
	struct bpf_program bpf_fp;
	if(pcap_compile(handle, &bpf_fp, filter_str, 1, 0) != -1)
		cout<<"pcap_compile success "<<endl;
	if(pcap_setfilter(handle, &bpf_fp) != -1)
		cout<<"pcap_setfilter success "<<endl;

	//array used to store the packet
	const u_char *packet;
	int counter = 0;
	while(packet = pcap_next(handle, &header)){
		cout<<"This is the "<<++counter<<"th packet"<<endl;
		//u_char *pkt_ptr = (u_char *)packet;
		//struct ip *ip_hdr = (struct ip *)pkt_ptr;

		//get the length of the ip
		//int packet_length = ntohs(ip_hdr -> ip_len);
		//cout<<"ip length: "<<packet_length<<endl;
		
		//get the epoch time 
		cout<<"Epoch time: "<<header.ts.tv_sec<<"."<<header.ts.tv_usec<<endl;
		
		//get the data
		cout<<"Total Packet length: "<<header.caplen<<endl;
		cout<<"Expect Packet length: "<<header.len<<endl;
		for(int i = 0; i < header.caplen; i++){
			//cout<<packet[i];
			cout<<hex<<uppercase<<setfill('0')<<packet[i]-'0';
		}
		cout<<endl;

		//package type
		struct ether_header *eth_header;
		eth_header = (struct ether_header *)packet;
		if(ntohs(eth_header -> ether_type) == ETHERTYPE_IP){
			cout<<"This is an ip package"<<endl;
		}else if(ntohs(eth_header -> ether_type) == ETHERTYPE_ARP){
			cout<<"This is an ARP package"<<endl;
		}else if(ntohs(eth_header -> ether_type) == ETHERTYPE_REVARP){
			cout<<"This is an Reverse ARP package"<<endl;
		}
		cout<<endl;

		//package type
		struct ip *ip1;
		ip1 = (struct ip*)(packet + sizeof(struct ether_header));

		//get destination ip
		cout<<"This is the destination ip: "<<ntohl(ip1 -> ip_dst.s_addr)<<endl;

		//get source ip
		cout<<"This is the source ip: "<<ntohl(ip1 -> ip_src.s_addr)<<endl;
		cout<<ip1 -> ip_p<<endl;
		if((ip1 -> ip_p) == IPPROTO_UDP){
			cout<<"This is a UDP protocol"<<endl;
		}else if((ip1 -> ip_p) == IPPROTO_ICMP){
			cout<<"This is a ICMP protocol"<<endl;
		}else if((ip1 -> ip_p) == IPPROTO_IP){
			cout<<"This is a IP protocol"<<endl;
		}else if((ip1 -> ip_p) == IPPROTO_TCP){
			cout<<"This is a TCP protocol"<<endl;
		}else{
			cout<<"Error protocol"<<endl;
		}
		cout<<endl;
	}
	pcap_close(handle);
	return 0;
}
