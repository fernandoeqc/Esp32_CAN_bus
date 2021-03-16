#include <Arduino.h>
#include <CAN.h>

#define LED1 2
#define BUT 27
#define LEN_COMM 5

char command[LEN_COMM] = {"desb"};

String bloq = "bloq";
String desb = "desb";

/* void detectBitRate()
{
    double bitRate[12] {1000E3, 500E3, 250E3, 200E3, 125E3, 100E3, 80E3, 50E3, 40E3, 20E3, 10E3, 5E3};
    CAN.observe();

    
    for (int i = 0; i < 12; i++)
    {
        if(CAN.begin(bitRate[i]))
        {
            Serial.println("Starting CAN failed!");
            while (1);
        }
        Serial.println(bitRate[i]);

        int time_old = millis();
        while(millis() - time_old < 1000)
        {
            
            int packetSize = CAN.parsePacket();
            if(packetSize)
            {   
                Serial.println("BirtRate:");
                Serial.println(bitRate[i]);
                break;
            }
        } 
    }
    Serial.println("fim");
} */

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

    //detectBitRate();
    //while (1);    
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



can nao funciona quando tira os resistores 120h