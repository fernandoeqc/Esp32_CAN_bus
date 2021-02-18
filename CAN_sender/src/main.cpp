#include <Arduino.h>
#include <CAN.h>

#define LED1 2
#define BUT 27
#define LEN_COMM 5

char command[LEN_COMM] = {"desb"};

String bloq = "bloq";
String desb = "desb";

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(BUT, INPUT_PULLUP);
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3))
  {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop()
{
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  if (digitalRead(BUT))
  {
    bloq.toCharArray(command, LEN_COMM);
    Serial.println(bloq);
    digitalWrite(LED1, HIGH);  
  }
  else
  {
    desb.toCharArray(command, LEN_COMM);
    Serial.println(desb);
    digitalWrite(LED1, LOW);
  }

  CAN.beginPacket(0x710);
  CAN.printf(command);
  CAN.endPacket();
  Serial.println("done");

  delay(1000);
}
