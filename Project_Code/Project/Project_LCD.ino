#include <LiquidCrystal.h>

const int switchPin = 8;
int sw_state = 0;
int presses = 0;
int val;
int oldval = 0;
int fan = 6;
float tempcal;
float luxval;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int led = 13;

void setup() {

  lcd.begin(16, 2);
  pinMode(switchPin,INPUT);
  pinMode(led,OUTPUT);
  pinMode(fan,OUTPUT); 

}

void loop() {

  val = digitalRead(switchPin);
  
  if ((val == LOW) && (oldval == HIGH)){
  presses = presses +1;

  delay(50);
  }

  oldval = val;

  digitalWrite(led,HIGH);

 switch(presses){

   case 0:

   lcd.setCursor(0,0);
   lcd.print("Aiden Ba");   
   
   lcd.setCursor(0,1);
   lcd.print("rrett   ");  

   break;

 case 1:  
   
   TEMP();

   lcd.setCursor(0,0);
   lcd.print("Temp =  ");
   
   lcd.setCursor(0,1);
   lcd.print(tempcal);
   delay(200);  

   break; 

case 2:  

   lcd.setCursor(0,0);
   lcd.print("Is it hu");
   
   lcd.setCursor(0,1);
   lcd.print("mid?    "); 
   break;  


case 3:  
    
   LIGHT();

   lcd.setCursor(0,0);
   lcd.print("Light = ");
   
   lcd.setCursor(0,1);
   lcd.print(luxval);
  delay(1000); 

   break;      

   default:

 presses = 0;

 }

}

void TEMP(void)
{
  float Rt = 4700;
  float ADC;
  float TB = 293.15; // TB = 25 degree celcius
  float BETA = 3950;
  float R = 5000;
  ADC = analogRead(A0);
  float temp, rtemp;
  float a,b;
  
  a = (R*ADC);
  b = (1023-ADC);
  Rt = a/b;
  
  temp = 1/((1/TB)+(1/BETA)*log(Rt/R));
  tempcal = temp-273.15;
  
  if(tempcal>=20)
  {
    digitalWrite(fan,HIGH); //fan on
  }
  else
  {
    digitalWrite(fan,LOW); //fan on
  }
  
}

void LIGHT(void)
{
float V;
float ADC2;
ADC2 = analogRead(A2);
V = ADC2*5.0/1023.0;
luxval = V*1333.0;
}

