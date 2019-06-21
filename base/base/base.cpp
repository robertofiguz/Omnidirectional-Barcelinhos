/*
  base.cpp - Library for Controlling the base.
  Created by Roberto Figueiredo, June 18, 2019.
*/

#include "Arduino.h"
#include "base.h"
#include "Wire.h"
#include "Ultrasonic.h"

base::base(int motor1_1, int motor1_2, int motor2_1, int motor2_2, int motor3_1, int motor3_2, int motor4_1, int motor4_2)
{
    Wire.begin();
    Serial.begin(19200);
    trigPin = A3;
    echoPin = A2;

    pinMode(motor1_1, OUTPUT);  // motor 1
    pinMode(motor1_2, OUTPUT);  // motor 1

    pinMode(motor2_1, OUTPUT);  // motor 2
    pinMode(motor2_2, OUTPUT);  // motor 2

    pinMode(motor3_1, OUTPUT);  // motor 3
    pinMode(motor3_2, OUTPUT);  // motor 3

    pinMode(motor4_1, OUTPUT);  // motor 4
    pinMode(motor4_2, OUTPUT);  // motor 4

    pinMode(trigPin,OUTPUT);
    pinMode(echoPin, INPUT);


}

void base::bracosStart(){
  Wire.beginTransmission(9);
  Wire.write(1);
  Wire.endTransmission();
//while make code run in loop until told otherwise?

}

void base::bracosStop(){
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
}

bool base::medir(){

  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

  if (distance<40){
    return true;
  }
  else{
    return false;
  }

}

void base::writeToMotors(int vel1, int vel2, int vel3, int vel4, int vel5, int vel6, int vel7, int vel8){
  motor1_1= 13;
  motor1_2 = 12;
  motor2_1 = 11;
  motor2_2 = 10;
  motor3_1 = 9;
  motor3_2 = 8;
  motor4_1 = 7;
  motor4_2 = 6;

  analogWrite(motor1_1,vel1);
  Serial.println("ran");
  Serial.println(motor1_1);
  Serial.println(vel1);
  analogWrite(motor1_2, vel2);

  analogWrite(motor2_1,vel3);
  analogWrite(motor2_2,vel4);

  analogWrite(motor3_1,vel5);
  analogWrite(motor3_2, vel6);

  analogWrite(motor4_1,vel7);
  analogWrite(motor4_2,vel8);

}
void base::diagonaldireita(int tempo)
{
    writeToMotors(150,0,150,0,150,0,150,0);
    delay(tempo); //check if this kinf of delay works, create variable for time
}

void base::diagonalesquerda(int tempo)
{
  writeToMotors(150,0,150,0,150,0,150,0);
  delay(tempo); //check if this kinf of delay works, create variable for time
}

void base::andarfrente(int tempo)
{
    writeToMotors(150,0,150,0,150,0,150,0);
    delay(tempo); //check if this kinf of delay works, create variable for time
}

void base::andartras(int tempo)
{
    writeToMotors(0,150,0,150,0,150,0,150);
    delay(tempo); //check if this kinf of delay works, create variable for time
}

void base::andaresquerda(int tempo)
{
  writeToMotors(150,0,0,150,0,150,150,0);
  delay(tempo);
}

void base::andardireita(int tempo)
{
  writeToMotors(0,150,150,0,150,0,0,150);
  delay(tempo);
}
void base::rodarCW(int tempo)
{
  //change code for compass and create variable for degrees and use while
  writeToMotors(0,150,150,0,0,150,150,0);
  delay(tempo);
   //delay(tempo); //check if this kinf of delay works, create variable for time
}


void base::rodarCCW(int tempo)
{
  //change code for compass and create variable for degrees and use while
  writeToMotors(150,0,0,150,150,0,0,150);
  delay(tempo);


}

void base::parar(int tempo)
{
  //change code for compass and create variable for degrees and use while
  writeToMotors(0,0,0,0,0,0,0,0);

  delay(tempo);
}



void base::rodarPublico()
{
  //change code for compass and create variable for degrees and use while
    ler_bussola();
    if(bearing<200 || bearing>220){
    while(bearing<200 || bearing>220)  // Enquanto o robô estiver desalinhado   ||->ou lógico   &&->e lógico (valor inicial)
 {
   rodarCW(100);//ver se e este ou rodar CCW
   ler_bussola();        //Ler a bússola
 }
}else if (bearing<0 || bearing>40){
  while(bearing<0 || bearing>40)  // Enquanto o robô estiver desalinhado   ||->ou lógico   &&->e lógico (valor inicial)
{
 rodarCCW(100);//ver se e este ou rodar CCW
 ler_bussola();        //Ler a bússola
}
}
 parar(10);


}


void base::ler_bussola()
{
  Wire.beginTransmission(ADDRESS);           //starts communication with CMPS10
  Wire.write(2);                              //Sends the register we wish to start reading from
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 4);              // Request 4 bytes from CMPS10
  while(Wire.available() < 4);               // Wait for bytes to become available
  highByte=Wire.read();
  lowByte = Wire.read();
  pitch = Wire.read();
  roll = Wire.read();
  bearing = ((highByte<<8)+lowByte)/10;      // Calcula full bearing
  fine = ((highByte<<8)+lowByte)%10;         // Calcula decimal place of bearing
  delay(100);
}
