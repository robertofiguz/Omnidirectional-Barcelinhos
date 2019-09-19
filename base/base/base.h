/*
  base.h - Library for Controlling the base.
  Created by Roberto Figueiredo, June 18, 2019.
*/

#ifndef base_h
#define base_h

#include "Arduino.h"
//#include "Servo.h" // include if end up creating class for the arms

class base
{
public:

  //bussola
    #define ADDRESS 0x60
    byte highByte, lowByte, fine;
    int bearing, pitch, roll;
    void ler_bussola();
//-------------------

//funções movimento
    void andarfrente(int tempo, int vel);
    void andartras(int tempo, int vel);
    void andaresquerda(int tempo, int vel);
    void andardireita(int tempo, int vel);
    void rodarCW(int tempo);
    void rodarCCW(int tempo);
    void parar(int tempo);
    void rodarPublico();
//-------------------
    bool medir();
    int trigPin;
    int echoPin;
    long duration;
    int distance;
    int motor1_1;
    int motor1_2;
    int motor2_1;
    int motor2_2;
    int motor3_1;
    int motor3_2;
    int motor4_1;
    int motor4_2;
    int vel1;
    int vel2;
    int vel3;
    int vel4;
    int vel5;
    int vel6;
    int vel7;
    int vel8;
    base(int motor1_1, int motor1_2, int motor2_1, int motor2_2, int motor3_1, int motor3_2, int motor4_1, int motor4_2);
    void writeToMotors(int vel1, int vel2, int vel3, int vel4, int vel5, int vel6, int vel7, int vel8);//check if this can be on private
    int convert(int vel);
    void StepUp(int vel);
  private:



};/*
class bracos
{
public:
  void
};
*/ //use same library for both just create separate classes for arms and base
#endif
