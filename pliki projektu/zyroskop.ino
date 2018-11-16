#include <Wire.h>

float stopnie = 180/3.141592654;
float kat_przyspieszania[2];
float kat_zyroskop[2];
float kat_koncowy[2];
float aktualny_czas, czas, poprz_czas;

int16_t acelerometr_osX;
int16_t acelerometr_osY;
int16_t acelerometr_osZ;
int16_t zyroskop_osX;
int16_t zyroskop_osY;
void setup() {
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  czas = millis();
  Serial.begin(9600);
}

void loop() {
  poprz_czas =czas;
  czas = millis();  
  aktualny_czas = (czas - poprz_czas) / 1000; 
  Wire.beginTransmission(0x68);            
  Wire.write(0x3B);                      
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);
  //dane z akcelerometru
  acelerometr_osX=Wire.read()<<8|Wire.read();
  acelerometr_osY=Wire.read()<<8|Wire.read();
  acelerometr_osZ=Wire.read()<<8|Wire.read();
  //obliczenia dla osi x 
  kat_przyspieszania[0] = atan((acelerometr_osY/16384.0)/sqrt(pow((acelerometr_osX/16384.0),2) + pow((acelerometr_osZ/16384.0),2)))*stopnie;
  //Obliczenia dla osi y
  kat_przyspieszania[1] = atan(-1*(acelerometr_osX/16384.0)/sqrt(pow((acelerometr_osY/16384.0),2) + pow((acelerometr_osZ/16384.0),2)))*stopnie;
  
  Wire.beginTransmission(0x68);
  Wire.write(0x43); 
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true);
  zyroskop_osX=Wire.read()<<8|Wire.read();
  zyroskop_osY=Wire.read()<<8|Wire.read();
  //obliczenia dla osi x
  kat_zyroskop[0] = zyroskop_osX/131.0;
  //obliczenia dla osi y
  kat_zyroskop[1] = zyroskop_osY/131.0;
  //dla osi x
  kat_koncowy[0] = 0.98 *(kat_koncowy[0] + kat_zyroskop[0]*aktualny_czas) + 0.02*kat_przyspieszania[0]; //filtr Kalamana dla osi x
  //dla osi y
  kat_koncowy[0] = 0.98 *(kat_koncowy[0] + kat_zyroskop[0]*aktualny_czas) + 0.02*kat_przyspieszania[0]; // filt Kalmana dla osi y
}
