
#include <jendefs.h>
#include <AppHardwareApi.h>
#include <AppQueueApi.h>

#include "clock.h"  
#include "node.h"
#include "task.h"

#include "sendToPc.h"
#include "tmpSensor.h"
#include "lightSensor.h"
#include "dio.h"
#include "mac.h"

#define USER_PACKET_TYPE 0x67

uint8 packet[2]; 
extern uint8 rx[127];
bool check=FALSE;
uint16 random=99;

void startNode()
{
sendToPcInit();
tmpInit();
macInit();
ledOff();
}

void userTaskHandler(uint8 taskType)
{
uint8 data, nodeId_High, nodeId_Low;

data=rx[0];
//nodeId_High=rx[1];
//nodeId_Low=rx[2];

	packet[0]=USER_PACKET_TYPE;
	packet[1]=data;
	//packet[2]=nodeId_High;
	//packet[3]=nodeId_Low;

check=sendDataToMac(packet,2,0xFFFF,0,FALSE);
	if(check==TRUE)
		random=99;
	else
		random=0;

updateAmbientdb(getNodeId(),random,packet[1]);
}


void userCriticalTaskHandler(uint8 critTaskType)
{

}

void userReceiveDataPacket(uint8* payload,uint8 length,uint16 prevAddr,uint8 linkQuality)
{
}



