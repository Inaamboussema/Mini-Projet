#include <SoftwareSerial.h>

SoftwareSerial espSerial(0, 1); // RX , TX  de la carte esp8266

int mot1=9;
int mot2=8;
int mot3=7;
int mot4=6;

int left=A0;
int right=A1;

int Left=0;
int Right=0;

void LEFT (void);
void RIGHT (void);
void STOP (void);

void setup()
{
  espSerial.begin(115200);
  while(!espSerial){;}
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
 Serial.begin(115200);

  pinMode(left,INPUT);
  pinMode(right,INPUT);

  digitalWrite(left,HIGH);
  digitalWrite(right,HIGH);
  
  
}

void loop() 
{
   int inChar;
 if (espSerial.available()) {
{
   inChar = espSerial.read();
  espSerial.print(inChar);
  Serial.println(inChar);
}
delay(1000);
}
Serial.print("receive from esp: ");
Serial.println(inChar);

analogWrite(mot1,255);
analogWrite(mot2,0);
analogWrite(mot3,255);
analogWrite(mot4,0);

while(1)
{
  Left=digitalRead(left);
  Right=digitalRead(right);
  
  if((Left==0 && Right==1)==1)
  LEFT();
  else if((Right==0 && Left==1)==1)
  RIGHT();
}
}

void LEFT (void)
{
   analogWrite(mot3,0);
   analogWrite(mot4,30);
   
   
   while(Left==0)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Right==0)
    {
      int lprev=Left;
      int rprev=Right;
      STOP();
      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(mot1,255);
    analogWrite(mot2,0); 
   }
   analogWrite(mot3,255);
   analogWrite(mot4,0);
}

void RIGHT (void)
{
   analogWrite(mot1,0);
   analogWrite(mot2,30);

   while(Right==0)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Left==0)
    {
      int lprev=Left;
      int rprev=Right;
     STOP();
      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(mot3,255);
    analogWrite(mot4,0);
    }
   analogWrite(mot1,255);
   analogWrite(mot2,0);
}
void STOP (void)
{
analogWrite(mot1,0);
analogWrite(mot2,0);
analogWrite(mot3,0);
analogWrite(mot4,0);
  
}







































/*Code Name: Arduino Line Follower Robot Car
Code URI: https://circuitbest.com/category/arduino-projects/
Author: Make DIY
Author URI: https://circuitbest.com/author/admin/
Description: This program is used to make Arduino Line Follower Robot Car.
Note: You can use any value between 0 to 255 for M1_Speed, M2_Speed, LeftRotationSpeed, RightRotationSpeed.
Here 0 means Low Speed and 255 is for High Speed.
Version: 1.0
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/

/*#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5


 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 80; // speed of motor 2
 int LeftRotationSpeed = 250;  // Left Rotation Speed
 int RightRotationSpeed = 250; // Right Rotation Speed


 void setup() {

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);

      pinMode(A0, INPUT); // initialize Left sensor as an input
      pinMode(A1, INPUT); // initialize Right sensor as an input

}

void loop() {

  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);

if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) {
    forward(); //FORWARD
}

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1) {
    right(); //Move Right
 }

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0) {
    left(); //Move Left
}

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1) {
    Stop();  //STOP
 }
}



void forward()
{
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void backward()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void right()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);

                analogWrite(enA, LeftRotationSpeed);
                analogWrite(enB, RightRotationSpeed);
}

void left()
{
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);

                analogWrite(enA, LeftRotationSpeed);
                analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
}*/

/*int signalPin_Gauche = 2; //c
int signalPin_Droite = A0; //capteur de ligne grove seeedstudio
int Motor1 = A1; // L293D - premier moteur pin 1 (Gauche)
int Motor2 = A2; // L293D - premier moteur pin 2 (Gauche)
int Motor3 = A3; // L293D - second moteur pin 1 (Droite)
int Motor4 = A4; // L293D - second moteur pin 2 (Droite)

void setup() {
  
pinMode(signalPin_Gauche, INPUT); 
pinMode(signalPin_Droite, INPUT);
pinMode(Motor1, OUTPUT); // Gauche
pinMode(Motor2, OUTPUT); // Gauche
pinMode(Motor3, OUTPUT); // Droite
pinMode(Motor4, OUTPUT); // Droite
//pinMode(Enable1_2 , OUTPUT);

Serial.begin(9600);
}


void loop()
{
  Serial.print("hii");
digitalWrite(Motor1, LOW); // Droite allumer
digitalWrite(Motor2, HIGH); // Droite allumer
digitalWrite(Motor3, LOW); //Gauche allumer
digitalWrite(Motor4, HIGH); //Gauche allumer

if(HIGH == digitalRead(signalPin_Gauche)) // si le capteur de gauche se met en etat HIGH le robot doit se deplacer ver la droite
{
  Serial.println("gauche");
digitalWrite(Motor3, LOW); // Droite eteint
digitalWrite(Motor4, LOW);  // Droite eteint
digitalWrite(Motor1, HIGH); // Gauche allumer
digitalWrite(Motor2, HIGH); // Gauche allumer
}

else // sinon on allume les 2 moteurs et le robot va tout droit
{
    Serial.println("tool");

digitalWrite(Motor1, HIGH); // Droite allumer
digitalWrite(Motor2, HIGH); // Droite allumer
digitalWrite(Motor3, HIGH); //Gauche allumer
digitalWrite(Motor4, HIGH); //Gauche allumer
}

if(HIGH == digitalRead(signalPin_Droite)) // si le capteur de droite se met en etat HIGH le robot doit se deplacer ver la gauche
{
    Serial.println("droite");

digitalWrite(Motor3, HIGH); // Droite allumer
digitalWrite(Motor4, HIGH); // Droite allumer
digitalWrite(Motor1, LOW); //Gauche eteint
digitalWrite(Motor2, LOW); //Gauche eteint
}

else // sinon on allume les 2 moteurs et le robot va tout droit
{
    Serial.println("tool");

digitalWrite(Motor1, HIGH); // Droite allumer
digitalWrite(Motor2, HIGH); // Droite allumer
digitalWrite(Motor3, HIGH); //Gauche allumer
digitalWrite(Motor4, HIGH); //Gauche allumer
}

}*/

