#include <SPI.h>

#include <LoRa.h>

#include <TinyGPS++.h>

#include <SoftwareSerial.h>

// Choose two Arduino pins to use for software serial

int RXPin = 0;

int TXPin = 1;   

// Create a TinyGPS++ object

TinyGPSPlus gps;

SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {

  Serial.begin(115200);

   gpsSerial.begin(9600);

  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {

    Serial.println("Starting LoRa failed!");

    while (1);

  }

  LoRa.setSyncWord(0xF3);

  

}

void loop() {

  

 while (gpsSerial.available() > 0)

    if (gps.encode(gpsSerial.read()))

    

        if (gps.location.isValid())

  {

    Serial.println("Sending to LoRa");

    LoRa.beginPacket();

    LoRa.print("Lat: ");

    LoRa.print(gps.location.lat(), 6);

    LoRa.print("c");

    LoRa.print("Long: ");

    LoRa.print(gps.location.lng(), 6);
Serial.print(gps.location.lng(), 6);
    Serial.println("Sent via LoRa");

    LoRa.endPacket();

  }

}
