#include <Servo.h>


#define MAX_SIGNAL 2000

#define MIN_SIGNAL 1000

#define MOTOR_PIN 9
#define MOTOR_PIN2 6
#define MOTOR_PIN3 5
#define MOTOR_PIN4 3
int value = 1000;

Servo silnik;
Servo silnik2;
Servo silnik3;
Servo silnik4;


void setup() {

  Serial.begin(9600);

  Serial.println("Przed podłączniem baterii należy skonfigurować ESC.");

  silnik.attach(MOTOR_PIN);
  silnik2.attach(MOTOR_PIN2);
  silnik3.attach(MOTOR_PIN3);
  silnik4.attach(MOTOR_PIN4);

  Serial.print("Ustawianie maksymalnej wartości dla silnika: (");Serial.print(MAX_SIGNAL);Serial.print("\n");

  Serial.println("Teraz można podłaczyć zasilanie, a następnie naciśnij dowolny klawisz");Serial.println("\n");

  silnik.writeMicroseconds(MAX_SIGNAL);
  silnik2.writeMicroseconds(MAX_SIGNAL);
  silnik3.writeMicroseconds(MAX_SIGNAL);
  silnik4.writeMicroseconds(MAX_SIGNAL);


  while (!Serial.available());

  Serial.read();

  Serial.print("Ustawianie minimalnej wartości dla silnika: (");Serial.print(MIN_SIGNAL);Serial.print("\n");

  silnik.writeMicroseconds(MIN_SIGNAL);
  silnik2.writeMicroseconds(MIN_SIGNAL);
  silnik3.writeMicroseconds(MIN_SIGNAL);
  silnik4.writeMicroseconds(MIN_SIGNAL);

  Serial.println("ESC zostało prawidłowo skonfigurowane");Serial.print("\n");

  Serial.println("Aby uruchomić silnik proszę wpisać liczby pomiędzy 1000 a 2000");

  Serial.println("Wpisanie liczby 1000 spowoduje zatrzymanie się silnik, podanie liczby 2000 spowoduje osiągnięcie przez silnik predkosci maksymalnej");


}



void loop() {

  if (Serial.available() > 0)

  {
    int value = Serial.parseInt();

    if (value > 999)
    {
      silnik.writeMicroseconds(value);
	  silnik2.writeMicroseconds(value);
	  silnik3.writeMicroseconds(value);
	  silnik4.writeMicroseconds(value);

      float predkosc = (value-1000)/10;

      Serial.print("\n");

      Serial.println("predkosc silnikow:"); Serial.print("  "); Serial.print(predkosc); Serial.print("%"); 
    }     
  }
}
