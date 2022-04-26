#include<Servo.h>

int echoS = 13;
int triggerS = 12;

int distanceS;
int durationS;

//Servo @11
int echoP = 10;
int triggerP = 9;

int distanceP;
int durationP;

int echoE = 4;
int triggerE = 2;

int distanceE;
int durationE;

int button = 8;

int light = 7;
int lightStatus = 0;  //To indicate if light is on or not
int pressed = 0;

int red = 6;
int green = 5;

Servo servo;
Servo servoE;
int positionE = 0;
int position = 0;

void setup() 
{

  Serial.begin(9600);
  Serial.println("Project Up and Running....");

  servo.attach(11, 500, 2500); 
  servoE.attach(3, 500, 2500);

  pinMode(echoS, INPUT);
  pinMode(triggerS, OUTPUT);

  pinMode(echoP, INPUT);
  pinMode(triggerP, OUTPUT);

  pinMode(echoE, INPUT);
  pinMode(triggerE, OUTPUT);

  pinMode(button, INPUT);

  pinMode(light, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop() 
{
  entrySystem();
  delay(500);
  slotAvailability();
  lightingSystem();
  delay(500);
  exitSystem();  
  delay(2000);
}

void entrySystem()
{
  digitalWrite(triggerS, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerS, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerS, LOW);
  durationS = pulseIn(echoS, HIGH);
  distanceS = durationS * 0.034 / 2;
  Serial.println("\nEntry System distance: ");
  Serial.print(distanceS);
  if(distanceS>15)
    servo.write(0);
  else
  {
    servo.write(90);
    delay(2000);
    servo.write(0);
  }
}

void slotAvailability()
{
  digitalWrite(triggerP, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerP, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerP, LOW);
  durationP = pulseIn(echoP, HIGH);
  distanceP = durationP * 0.034 / 2;
  Serial.println("\nSlot Availability distance: ");
  Serial.print(distanceP);
  if(distanceP<10)
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
  else
  {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  }
}

void lightingSystem()
{
  if(pressed>0 && pressed<5)
  {
    pressed++;
    return;
  }

  if(pressed == 5)
    pressed=0;
  int val = analogRead(A0);
  Serial.print("\nLight reading: ");
  Serial.print(val);
  
  if(digitalRead(button)==0)
  {
    pressed = 1;
    Serial.print("Button Pressed");
    if(lightStatus)
    {
      digitalWrite(light, LOW);
      lightStatus = 0;
    }
    else
    {
      digitalWrite(light, HIGH);
      lightStatus = 1;
    }
    return;
  }
  if(val<30)
  {
    digitalWrite(light, HIGH);
    lightStatus = 1;
  }
  else
  {
    digitalWrite(light, LOW);
    lightStatus = 0;
  }
}

void exitSystem()
{
  digitalWrite(triggerE, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerE, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerE, LOW);
  durationE = pulseIn(echoE, HIGH);
  distanceE = durationE * 0.034 / 2;
  Serial.println("\nExit System distance: ");
  Serial.print(distanceE);
  if(distanceE>15)
    servoE.write(0);
  else
  {
    servoE.write(90);
    delay(2000);
    servoE.write(0);
  }
}
