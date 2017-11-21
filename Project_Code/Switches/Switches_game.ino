
#include <LiquidCrystal.h>

const int switchPin = 8;
int fan = 6;
int sw_state = 0;
int presses = 0;
int val;
int oldval = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int led = 13;
float tempcal;
float luxval;

void setup() {
   
  lcd.begin(8, 2);
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
   lcd.print("Peter B0");
   lcd.setCursor(0,1);
   lcd.print("0069188 ");   
   break;
 
 case 1:  
   TEMP();
   
   lcd.setCursor(0,0);
   lcd.print("Temp =  ");
   lcd.setCursor(0, 1); 
   delay(200);
   lcd.print(tempcal);
   lcd.setCursor(4,1);
   lcd.print(" oC ");   
   break;
   
  case 2:  
   
   lcd.setCursor(0,0);
   lcd.print("Humidity");
   lcd.setCursor(0,1);
   lcd.print(" =     %");
   break;  
  
 case 3:
   LIGHT();   
   lcd.setCursor(0,0);
   lcd.print("Light =  ");
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
  float Rt = 1200;
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

