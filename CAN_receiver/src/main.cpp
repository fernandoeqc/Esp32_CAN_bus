#include <Arduino.h>
#include <CAN.h>

String bloq = "bloq";
String desb = "desb";

#define LED1 2

//apagar projeto, criar novo e colar arquivos do github

void setup()
{
    pinMode(LED1, OUTPUT);
    
    Serial.begin(115200);
    while (!Serial);

    Serial.println("CAN Receiver");

    // start the CAN bus at 500 kbps
    if (!CAN.begin(500E3))
    {
        Serial.println("Starting CAN failed!");
        while (1);
    }

    CAN.filter(0x710);
}

void loop()
{
    String dados;

    // try to parse packet
    int packetSize = CAN.parsePacket();

    if (packetSize)
    {
        // received a packet
        Serial.print("Received ");

        if (CAN.packetExtended())
        {
            Serial.print("extended ");
        }

        if (CAN.packetRtr())
        {
            // Remote transmission request, packet contains no data
            Serial.print("RTR ");
        }

        Serial.print("packet with id 0x");
        Serial.print(CAN.packetId(), HEX);

        if (CAN.packetRtr())
        {
            Serial.print(" and requested length ");
            Serial.println(CAN.packetDlc());
        }
        else
        {
            Serial.print(" and length ");
            Serial.println(packetSize);

            // only print packet data for non-RTR packets
            dados = CAN.readString();

            if (dados.equals(bloq))
            {
                digitalWrite(LED1, HIGH);
            }
            else
            {
                digitalWrite(LED1, LOW);
            }

            Serial.print(dados);
        }

        Serial.println();
    }
}
