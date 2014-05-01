//----------------------------------------------------------------------------------------------------------------------
// This program is based on:
// TinyTX Simple Receive Example
// By Nathan Chantrell. 
//
// Licenced under the Creative Commons Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0) licence:
// http://creativecommons.org/licenses/by-sa/3.0/
//----------------------------------------------------------------------------------------------------------------------
// Output to serial interface was redesigned by Reinhard Nickels

#include <JeeLib.h> // https://github.com/jcw/jeelib

// Fixed RF12 settings
#define MYNODE 30            //node ID of the receiever
#define freq RF12_868MHZ     //frequency
#define group 210            //network group

typedef struct {
  int humidity;	// Humidity reading
  int supplyV;	// Supply voltage
  int temp;	// Temperature reading
  unsigned long boots;   // minutes since boot, nach 49 Tagen Überlauf
} 
Payload;
Payload rx;

int nodeID;    //node ID of tx, extracted from RF datapacket. Not transmitted as part of structure
unsigned long last_s;

void setup () {
  Serial.begin(115200);
  rf12_initialize(MYNODE, freq,group); // Initialise the RFM12B
//  Serial.println("TinyTX Simple Receive Example");
//  Serial.println("-----------------------------");
  Serial.println("Waiting for data");
}

void loop() {
  if (rf12_recvDone() && rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0) {
    nodeID = rf12_hdr & 0x1F;  // get node ID
    rx = *(Payload*) rf12_data;
    int humidity = rx.humidity;
    int supplyV = rx.supplyV;
    int temp = rx.temp;
    unsigned long btime = rx.boots;
    if (RF12_WANTS_ACK) {                  // Send ACK if requested
      rf12_sendStart(RF12_ACK_REPLY, 0, 0);
//      Serial.print("ack\t");
    }
    Serial.print(nodeID);
    Serial.print("\t");
    Serial.print(supplyV);
    Serial.print("\t");
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(humidity);
    Serial.print("\t");
    Serial.print(btime);
    Serial.print("\t");
    unsigned long rectime = millis()/1000;
    Serial.print(rectime);
    Serial.print("\t");
    Serial.println(rectime -last_s); 
    last_s = millis()/1000;
  }
}

