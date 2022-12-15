'''
Arduino code for laser tag game by Bala Venkataraman

December 15, 2022
'''

#include <IRremote.h> // include the IRremote library
#define RECEIVER_PIN 7 // define the IR receiver pin
#define HB_1 8 // define the pins for the health bar lights
#define HB_2 9
#define HB_3 10
#define HB_4 11
#define HB_5 12
#define buzzer_pin 6 // define the pin for the buzzer

IRrecv receiver(RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results results; // create a results object of the decode_results class
long shoot_val = 16718055; // The value of the button on the remote that corresponds to the trigger
int health = 5; // starting health value
bool death = false; //death state

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600
  receiver.enableIRIn(); // enable the receiver
  pinMode(7, INPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);///
  pinMode(12, OUTPUT);

} 
void updatehealth(){ // update the health bar lights
    if(health > 4){
      digitalWrite(HB_5, HIGH);
    }
    else{
      digitalWrite(HB_5, LOW);      
    }
    if(health > 3){
      digitalWrite(HB_4, HIGH);
    }
    else{
      digitalWrite(HB_4, LOW);      
    }
    if(health > 2){
      digitalWrite(HB_3, HIGH);
    }
    else{
      digitalWrite(HB_3, LOW);      
    }
    if(health > 1){
      digitalWrite(HB_2, HIGH);
    }
    else{
      digitalWrite(HB_2, LOW);      
    }
    if(health > 0){
      digitalWrite(HB_1, HIGH);
    }
    else{
      digitalWrite(HB_1, LOW);      
    }
}

void loop() {
  updatehealth(); // call the function to update the health bar lights
  if (receiver.decode(&results)) { // decode the received signal and store it in results
    if(results.value  == shoot_val){ // if player is shot
      health -= 1; // decrement health when shot
      if(health > 0){
        for(int i = 0; i < 50; i++){ // play hit sound  (100hz tone), engage cooldown delay of 500ms
        digitalWrite(buzzer_pin, HIGH);
        delay(5);
        digitalWrite(buzzer_pin, LOW);
        delay(5);
        }
      }
      else{
        if(!death){
        death = true; // set death state
        digitalWrite(buzzer_pin, HIGH); // play death sound (600hz tone) for 3 seconds
        delay(3000);
        digitalWrite(buzzer_pin, LOW);
        }
      }
    } 
    receiver.resume(); // reset the receiver to detect the next shot
    
  }

}
