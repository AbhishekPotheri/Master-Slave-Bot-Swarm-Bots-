
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 3;


int motorpin1 = 7;
int motorpin2 = 6; //For left motor
int motorpin3 = 5;
int motorpin4 = 4; //For right motor

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();

  pinMode(motorpin1, OUTPUT); //This sets the module as receiver
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
}
void loop()
{
  
 while (!Serial && (millis() < 2000));
  if (radio.available())              //Looking for the data.
  {
    char text[32] = "", ans; //Saving the incoming data
    radio.read(&text, sizeof(text));//Reading the data
    //strcpy(ans,text);
    Serial.write(text);
 

    if (strcmp(text, "LEFT") == 0)
      right();
    else if (strcmp(text, "RIGHT") == 0)
      left();
    else if (strcmp(text, "FORWARD") == 0)
      forward();
    delay(150);
    //asm volatile("jump 0");
  }
}
void stop()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
  //analogWrite(enA,255);
  //analogWrite(enB,255);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, LOW);
  delay(25);
}

void forward()
{
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  // analogWrite(enA,255);
  //analogWrite(enB,255);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}


void backward()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  // analogWrite(enA,255);
  // analogWrite(enB,255);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
}


void left()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  // analogWrite(enA,255);
  //analogWrite(enB,255);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}


void right()
{
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  //analogWrite(enA,255);
  //analogWrite(enB,255);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
}
