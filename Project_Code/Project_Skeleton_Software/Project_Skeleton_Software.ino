/*
  Greenhouse Environmental Monitering and Control BN001 Year 2 Project 2013
  by aiden barrett
  
 */

// include the library code:
#include <LiquidCrystal.h>


// *** Variable decalarations ***

const int switchPin = 8; //Mode select switch input pin
int sw_state = 0; //new value of the mode switch
int no_of_switch_presses =0; //number of presses of the mode switch
int val;// store val of mode switch
int old_val=0; //store the previous value of valof the mode switch


void setup() {
  
 
  pinMode(switchPin,INPUT); // Set as input for the mode switch

}

void loop() {
  // **** Mode Select  **** 
  
  val = digitalRead(switchPin); // Read the mode switch
    if ((val == LOW) && (old_val ==HIGH) {
    no_of_switch_presses = no_of_switch_presses +1;
   //Update the number of switch presses and inplement soft switch debounce
   delay(50); // 50ms debounce delay
    }
    old_val = val; //val is now old so store it
    
    // Display whichever dipslay mode has been selected
 switch (no_of_switch_presses) {
 case 0: 
 // *** Welcome Message ***
 
       break;
 case 1:
 
  // ** TEMPERATURE MODE **
                    

  // print the current temperature value:
  
  
        break; // end temperature case
 
 
 
 
 case 2: 
 // ** HUMIDITY MODE **
                     
   
  // print the current humidity value:
  
         break;// end humidity case
  
   case 3:
 
  // ** Light Level MODE **
                    

  // print the current light level value:
  
  
          break; // end light level case
  default:
  
  // ** Last Mode so setup to Start Selection Again **
              no_of_switch_presses = 0;
  // reset so that we cycle through the choices again
  
   } // end of switch case 
   // ***** End of Mode Select and LCD Display Code ****
   
   
   
 //Call Measurement Functions

}// End loop function

// ****** Measurement Functions *****
// you can seperate out all your measurement and calcualtions into seperate functions
