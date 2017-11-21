/*
  Greenhouse Environmental Monitering and Control BN0012 Year 2 Project 2015
  by B00075033  https://aidenbarrett.wordpress.com/ 
  
 */

// include the library code:
#include <LiquidCrystal.h> 


// *** Variable decalarations *** 

  const int switchPin = 8; // Mode select switch input pin
  int sw_state = 0; // New value of the mode switch
  int switch_presses = 0; // Number of presses of the mode switch
  int val; // Stores val of mode switch
  int oldval = 0; //Stores the previous value of the mode switch
 
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // The interface pin numbers
 
  int led = 13; // sets up LED pin
  int fan = 6; // sets up fan pin.
  float temperature;
  float lux_value;
 
void setup() { 
 
    lcd.begin(8, 2); 
    pinMode(switchPin,INPUT); // Set as input for the mode switch
    pinMode(led,OUTPUT); // Set as output for LED
    pinMode(fan,OUTPUT); // Set as output for fan
    pinMode(A0, INPUT); // Sets A0 as temperature input pin
    pinMode(A2, INPUT); // Sets A2 as light sensor input pin
 
  } 
 
  void loop() { 
    
    // **** Mode Select  **** 
 
    val = digitalRead(switchPin); // Read the mode switch
    
    //Update the number of switch presses and inplement soft switch debounce
    if ((val == LOW) && (oldval == HIGH)){ 
    switch_presses = switch_presses +1; 
 
    delay(50); // 50ms debounce delay
    } 
 
    oldval = val; //val is now old so store it
 
    digitalWrite(led,HIGH); 
 
    // Display whichever dipslay mode has been selected
    switch(switch_presses){ 
 
   case 0: 
 
     // *** Welcome Message ***
     lcd.setCursor(0,0);  // Greeting message
     lcd.print("Aidens P");   
     
     lcd.setCursor(0,1); 
     lcd.print("roject  ");  
 
     break; 
 
  case 1:  
     
     // ** TEMPERATURE MODE **
     
     TEMP();
     
     lcd.setCursor(0,0); 
     lcd.print("Temp:   "); 
     //delay(200);
     lcd.setCursor(0,1); 
     lcd.print(temperature);  
     lcd.setCursor(5,1);
     lcd.print("oC ");
 
     break; 
 
  case 2:  
     
     // ** HUMIDITY MODE **
     lcd.setCursor(0,0); 
     lcd.print("Humidity"); 
     
     lcd.setCursor(0,1); 
     lcd.print(" Mode   "); 
      
     break;  
 
  case 3:  
     
     // ** Light Level MODE **
     LIGHT();
     
     lcd.setCursor(0,0); 
     lcd.print("Light:  "); 
     
     lcd.setCursor(0,1); 
     lcd.print(lux_value); 
     //delay(700);
     lcd.setCursor(5,1);
     lcd.print("lx"); // lx, measure of one lumen per square metre.
     
     break;
   
  case 4: 
 
     // *** Fan ON Mode ***
     lcd.setCursor(0,0); 
     lcd.print("Fan Mode");   
     
     lcd.setCursor(0,1); 
     lcd.print(": On    ");
     digitalWrite(fan,HIGH);  
 
     break;   
  
   case 5: 
 
     // *** Fan OFF Mode ***
     lcd.setCursor(0,0); 
     lcd.print("Fan Mode");   
     
     lcd.setCursor(0,1); 
     lcd.print(": Off    "); 
     digitalWrite(fan,LOW); 
 
     break; 
     
     default: 
   
   // ** Last Mode so setup to Start Selection Again **
   switch_presses = 0; 
 
  } // end of switch cases
  
  delay(300); // more managable delay, reduce polling delay between presses.
  lcd.clear(); // clear screen
 
 } // end void loop
 
void TEMP(void)
{
  float Rt = 4700;
  float ADC;
  float init_kelvin = 298.15; // 25 degrees celcius in kelvin
  float BETA = 3950; // Beta constant
  float Rth = 5000; // Resistance of thermistor at 25 degrees celcius
  
  ADC = analogRead (A0); // reads analog pin A0
  
  float temp, rtemp;
  float a;
  float b;
  
  // thermister multiplied by ADC value, divided by, the ADC value minus 1023.
  a = (Rth * ADC); 
  b = (1023 - ADC);
  Rt = a / b;
  
  temp = 1 / ( (1/init_kelvin) + (1/BETA) * log (Rt/Rth) ); // steinhart equation
  temperature = temp - 273.15; // temperature converted to celcius;
  
  if (temperature >= 28)
  {
    digitalWrite(fan,HIGH); //fan on
  }
  
  else
  {
    digitalWrite(fan,LOW); //fan on
  }
  
}

void LIGHT (void)
{
  
float voltage;
float ADC2;

ADC2 = analogRead(A2); //analog read from pin A2

voltage = ADC2 * 5.0 / 1023.0;
lux_value = voltage * 1333.0; 

}

