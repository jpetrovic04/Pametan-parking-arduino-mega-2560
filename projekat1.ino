#include <LiquidCrystal.h>
#include <Servo.h>
#include <TimerOne.h>


#define button1 53 //d
#define servo 52


#define servo2 50
#define trigRampa 9
#define echoRampa 8


#define red1 22
#define green1 23
#define trig1 24
#define echo1 25


#define red2 26
#define green2 27
#define trig2 28
#define echo2 29


#define red3 30
#define green3 31
#define trig3 32
#define echo3 33


#define red4 34
#define green4 35
#define trig4 36 //skinutiii
#define echo4 37 //skinutiii


Servo rampa,rampa2; //pbjekat za konptrolu servo motora


const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
String poruka = "";
LiquidCrystal mojLCD(rs, en, d4, d5, d6, d7);


int btnState = 0;
volatile int buttonPressed = 0;
int lastBtnState = 0;


const int limit = 5;
bool taken;


int counter = 0;
int lastCounter = -1;
bool rampaAktivna = false;


int reloadParking(int trig, int echo, int red, int green, String placeNumber)
{
  long distance = range(trig, echo);
  taken = (distance > 0 && distance < limit);
  
  if(taken){
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    return 0;


  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    return 1;
  }
}


long range(int trig,int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);


  long duration = pulseIn(echo, HIGH, 30000);
  return duration/58;
}


void btnTimerISR()
{
  btnState = digitalRead(button1);
  if(btnState != lastBtnState)
  {
    if(btnState == HIGH)
    {
      buttonPressed = 1;
    }
    lastBtnState = btnState; 
  } 
} 
void setup() {
  // put your setup code here, to run once:
pinMode(button1, INPUT);


rampa.attach(servo);
rampa.write(0);
rampa2.attach(servo2);
rampa2.write(30);
delay(200);
rampa.detach();
rampa2.detach();



pinMode(red1, OUTPUT);
pinMode(green1, OUTPUT);
pinMode(trig1, OUTPUT);
pinMode(echo1, INPUT);


pinMode(red2, OUTPUT);
pinMode(green2, OUTPUT);
pinMode(trig2, OUTPUT);
pinMode(echo2, INPUT);


pinMode(red3, OUTPUT);
pinMode(green3, OUTPUT);
pinMode(trig3, OUTPUT);
pinMode(echo3, INPUT);


pinMode(red4, OUTPUT);
pinMode(green4, OUTPUT);
pinMode(trig4, OUTPUT);
pinMode(echo4, INPUT);


pinMode(trigRampa, OUTPUT);
pinMode(echoRampa, INPUT);


mojLCD.begin(16,2);
mojLCD.setCursor(1,0);
mojLCD.print("Smart Parking");
delay(2000);
mojLCD.clear();


Timer1.initialize(50000);
Timer1.attachInterrupt(btnTimerISR);


Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly
  counter=0;
  int duzina = 0; 
  if(!rampaAktivna){
    int trenutnoSlobodno = 0;
  trenutnoSlobodno += reloadParking(trig1, echo1, red1, green1, "Mesto 1");
  trenutnoSlobodno += reloadParking(trig2, echo2, red2, green2, "Mesto 2");
  trenutnoSlobodno += reloadParking(trig3, echo3, red3, green3, "Mesto 3");
  trenutnoSlobodno += reloadParking(trig4, echo4, red4, green4, "Mesto 4");
  
  counter = trenutnoSlobodno;


  if(counter != lastCounter){
  mojLCD.clear();
  mojLCD.setCursor(1,0);
  mojLCD.print("Smart Parking");
  mojLCD.setCursor(2, 1);
  mojLCD.print("slobodno: ");
  mojLCD.print(counter);


  lastCounter = counter;
  }
  delay(300);
  }


  duzina = range(trigRampa, echoRampa);
  Serial.println("Duzina rampa: "+ String(duzina));
  if(duzina > 0 && duzina <= 4)
  {
    rampa2.attach(servo2);
    rampa2.write(120);
    delay(200);
    rampa2.detach();
    delay(4200);


    rampa2.attach(servo2);
    rampa2.write(30);
    delay(200);
    rampa2.detach();
  }


  if(buttonPressed == 1)
  {
    rampaAktivna = true;
    mojLCD.clear();
    if(counter > 0)
    {
      mojLCD.setCursor(3,0);
      mojLCD.print("Dobrodosli!");
      mojLCD.setCursor(2,1);
      mojLCD.print("Rampa se dize");
      delay(500);


      rampa.attach(servo);
      rampa.write(90);
      delay(100);
      rampa.detach();
      delay(4200);


      mojLCD.clear();
      mojLCD.setCursor(2, 0);
      mojLCD.print("Rampa se spusta");


      rampa.attach(servo);
      rampa.write(0);
      delay(100);
      rampa.detach();
    }
    else
    {
      mojLCD.setCursor(2, 0);
      mojLCD.print("NEMA MESTA!");
      mojLCD.setCursor(1, 1);
      mojLCD.print("Parking je pun");
      delay(3000); // Dr?i poruku 3 sekunde na ekranu 
    }
    buttonPressed = 0;
    rampaAktivna= false;
    lastCounter = -1;
  }
}