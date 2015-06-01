
#ifndef PACKETS_H

#define PACKETS_H

typedef struct packet{
        int pid;
        int length;
        char* data;
}Packet;

void printPacket(Packet p);

Packet initPacket(int pid,int length,char* data);

void cleanPackets(Packet* packets,int N);

int isPacketInt(Packet p);

int isPacketData(Packet p);

int isValidPacket(Packet p);

int writePacket(int fd,Packet p);

int readPacket(int fd,Packet* p);

#endif


