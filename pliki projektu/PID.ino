#include <Wire.h>
#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN 9
#define MOTOR_PIN2 10

Servo silnik;//prawy
Servo silnik2;//lewy

float stopnie = 180/3.141592654;
float kat_przyspieszania[2];
float kat_zyroskop[2];
float kat_koncowy[2];
float aktualny_czas, czas, poprz_czas;
float PID, pwmLewy, pwmPrawy, odchylenie,poprzedni_blad;
int16_t acelerometr_osX;
int16_t acelerometr_osY;
int16_t acelerometr_osZ;
int16_t zyroskop_osX;
int16_t zyroskop_osY;

float pid_p=0;
float pid_i=0;
float pid_d=0;

double kp=1;
double ki=0;
double kd=0;

double moc_poczatkowa=1150; //wartosc wyjsciowa silnikow

void setup() {
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);
  silnik.attach(MOTOR_PIN2);//prawy
  silnik2.attach(MOTOR_PIN);//lewy
  czas = millis();
  silnik2.writeMicroseconds(1000); 
  silnik.writeMicroseconds(1000); 
  Serial.println("podlacz baterie w ciagu 8 sekund");
  delay(8000);
}

void loop() {
  poprz_czas =czas;
  czas = millis();  
  aktualny_czas = (czas - poprz_czas) / 1000; 
  Wire.beginTransmission(0x68);            
  Wire.write(0x3B);                      
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true);
  //dane z akcelerometru
  acelerometr_osX=Wire.read()<<8|Wire.read();
  acelerometr_osY=Wire.read()<<8|Wire.read();
  acelerometr_osZ=Wire.read()<<8|Wire.read();
  //obliczenia dla osi x 
  kat_przyspieszania[0] = atan((acelerometr_osY/16384.0)/sqrt(pow((acelerometr_osX/16384.0),2) + pow((acelerometr_osZ/16384.0),2)))*stopnie;
  //Obliczenia dla osi y
  kat_przyspieszania[1] = atan(-1*(acelerometr_osX/16384.0)/sqrt(pow((acelerometr_osY/16384.0),2) + pow((acelerometr_osZ/16384.0),2)))*stopnie;
  
  Wire.beginTransmission(0x68);
  Wire.write(0x43); //0x3B
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
  kat_koncowy[1] = 0.98 *(kat_koncowy[0] + kat_zyroskop[0]*aktualny_czas) + 0.02*kat_przyspieszania[0]; // filt Kalmana dla osi y
Serial.println(kat_koncowy[1]);

odchylenie = kat_koncowy[1]-0;
pid_p = kp * odchylenie;
 if(-4 <odchylenie<4)
 {
  pid_i = pid_i+(ki*odchylenie);
 }
pid_d=kd*((odchylenie-poprzedni_blad)/aktualny_czas);
PID = pid_p + pid_i + pid_d;
if(PID < -1000)
{
  PID=-1000;
}
if(PID > 1000)
{
  PID=1000;
}


pwmLewy =  moc_poczatkowa + PID;
pwmPrawy =  moc_poczatkowa - PID;

if(pwmLewy < 1000)
{
  pwmLewy= 1000;
}
if(pwmLewy > 1500)
{
  pwmLewy=1500;
}


if(pwmPrawy < 1000)
{
  pwmPrawy= 1000;
}
if(pwmPrawy > 1500)
{
  pwmPrawy=1500;
}



//Serial.println("predkosc silnikow:"); Serial.print("  "); Serial.print(pwmLeft); Serial.print("%"); 
//Serial.print("\n");
//Serial.println("predkosc silnikow:"); Serial.print("  "); Serial.print(pwmRight); Serial.print("%"); 
//Serial.print("\n");
silnik2.writeMicroseconds(pwmLewy);
silnik.writeMicroseconds(pwmPrawy);
poprzedni_blad = odchylenie;

}
