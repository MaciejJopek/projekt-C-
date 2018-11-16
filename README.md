# Projekt - Dron

## Opis
 Celem projektu jest budowa drona *od podstaw*. Konieczne bedzie zaprogramowanie kontrolera lotu
opartego o płytkę arduino. Zadaniem wyżej wymienionego elemetu będzie:
 1. pobieranie wartości z żyroskopu oraz akcelerometru .
 2. zarządzanie  prędkością silników.
 3. komunikacja z pilotem.

 Dodatkowo zostanie również zaprogramowany pilot, który bedzie odczytywał wartości z joysticków i  wysyłał je do drona.

 W projekcie bedzie wykorzystywane biblioteki:
* Servo, która umożliwia Arduino kontrolowanie 4 silników bezszczotkowych wykorzystywanych przy budownie drona.
* MPU6050, która pozwala na odczyt danych z akcelerometru i żyroskopu potrzebnych do stabilizacji lotu 
* Wire.h blioteka umożliwiająca komunikację z urządzeniami I2C / TWI
