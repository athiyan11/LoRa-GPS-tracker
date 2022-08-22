
#include <SPI.h> //SPI Library 

#include <LoRa.h> //LoRa Library 

#include <LiquidCrystal_I2C.h> //Library for LCD

#define ss 5
#define rst 14
#define dio0 2

int lcdColumns = 16;
int lcdRows = 2;

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Initialize LCD method
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {

  Serial.begin(9600); //Serial for Debugging 

  

  lcd.begin(); //Initialise 16*2 LCD

  lcd.print("Arduino LoRa"); //Intro Message line 1

  lcd.setCursor(0, 1);

  lcd.print("Receiver"); //Intro Message line 2

  delay(2000);

  

  if (!LoRa.begin(433E6)) { //Operate on 433MHz

    Serial.println("Starting LoRa failed!");

    lcd.print("LoRa Failed");

    while (1);

  }

}

void loop() {

  int packetSize = LoRa.parsePacket();

  

  if (packetSize) {     // If packet received

    Serial.print("Received packet '");

    lcd.clear();

    while (LoRa.available()) {

      char incoming = (char)LoRa.read();

      if (incoming == 'c')

      {

        lcd.setCursor(0, 1);

      }

      else

      {

        lcd.print(incoming);

      }

      

    }

  }

}
