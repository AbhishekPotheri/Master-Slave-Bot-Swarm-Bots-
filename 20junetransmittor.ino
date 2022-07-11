#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";

int c;
int enA=A3;
int enB=A4;
int enC=A5;
int motorpin1=7;
int motorpin2=6;  //For left motor
int motorpin3=5;
int motorpin4=4;  //For right motor

int centerIR;
int leftIR;
int rightIR;

int leftFlag=0;
int centerFlag=0;
int rightFlag=0;

void setup()
{
  Serial.begin(9600);
  //Setup motors
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  pinMode(motorpin3,OUTPUT);
  pinMode(motorpin4,OUTPUT);
  pinMode(enA,INPUT);
  pinMode(enB,INPUT);
  pinMode(enC,INPUT);
  radio.begin();
  radio.openWritingPipe(address);   
  radio.setPALevel(RF24_PA_MIN);      
  radio.stopListening();       
}

void loop() {
    centerIR = digitalRead(A3);
    leftIR   = digitalRead(A4);
    rightIR  = digitalRead(A5);
    Serial.print(centerIR);
     Serial.print(leftIR);
      Serial.print(rightIR);
  
    
    
    if(leftIR==0)
      leftFlag=1;
    else 
      leftFlag=0;

   if(rightIR==0)
      rightFlag=1;
   else 
      rightFlag=0;

   if(centerIR==0)
      centerFlag=1;
   else 
      centerFlag=0;
  
   if((leftFlag==1)||(rightFlag==1)||(centerFlag==1))
   {
    if(centerFlag==1)
    {
     if(leftFlag==1)
     {
      right();
      const char text[] = "RIGHT";
      radio.write(&text, sizeof(text));
     }
    
     else if (rightFlag ==1)
     { 
      left();
      const char text[] = "LEFT";
      radio.write(&text, sizeof(text));
     }
     else
     {
      left();
      const char text[] = "LEFT";
      radio.write(&text, sizeof(text));
     }
    }
    else if (leftFlag==1)
    {
     right();
     const char text[] = "RIGHT";
     radio.write(&text, sizeof(text)); 
    }
    else if(rightFlag==1)
    {
      left();
      const char text[] = "LEFT";
      radio.write(&text, sizeof(text));
    }
    else
    {
      left();
      const char text[] = "LEFT";
      radio.write(&text, sizeof(text));
    }
   }
     else
      {
       forward();
       const char text[] = "FORWARD";
       radio.write(&text, sizeof(text)); }

}
  
  // drive.....................................................................//
  void stop()
  {
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,LOW);
  //digitalWrite(enA,255);
  //digitalWrite(enB,255);
  digitalWrite(motorpin3,LOW);
  digitalWrite(motorpin4,LOW);
  delay(25);
  }

  
  void forward()
  {
   
    
 Serial.println("Foward");
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
 // digitalWrite(enA,255);
  //digitalWrite(enB,255);
  digitalWrite(motorpin3,HIGH);
  digitalWrite(motorpin4,LOW); 
  }

  
  void backward()
  {
    Serial.println("Backward");
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
 // digitalWrite(enA,255);
 // digitalWrite(enB,255);
  digitalWrite(motorpin3,LOW);
  digitalWrite(motorpin4,HIGH); 
  }

  
  void left()
  {
   Serial.println("Left");
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
 // digitalWrite(enA,255);
  //digitalWrite(enB,255);
  digitalWrite(motorpin3,HIGH);
  digitalWrite(motorpin4,LOW); 
  }

  
  void right()
  {
Serial.println("Right");
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
 //digitalWrite(enA,255);
  //digitalWrite(enB,255);
  digitalWrite(motorpin3,LOW);
  digitalWrite(motorpin4,HIGH);
  }
  
  
