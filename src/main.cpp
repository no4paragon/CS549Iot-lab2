#include <Arduino.h>

#define RED_PIN GPIO_NUM_32 // define red led (STOP)
#define YELLOW_PIN GPIO_NUM_33 // define yellow (READY)
#define GREEN_PIN GPIO_NUM_25 // define green (GO)
#define BUTTON_PIN GPIO_NUM_36 // define button pin
#define BUZZER_PIN GPIO_NUM_15 // define buzzer pin

// Hard coded enumerator
#define RED_STATE 0
#define RED_YELLOW_STATE 1
#define YELLOW_STATE 2
#define GREEN_STATE 3

#define RED_MILLIS 10000 // red for 10 sec
#define YELLOW_MILLIS 2000 // yellow for 2 sec
#define RED_YELLOW_MILLIS 2000 // yellow red for 2 sec.
#define GREEN_MILLIS 5000 // green for 5sec

int tl_state;           // Traffic light state.
unsigned long tl_timer; // Traffic light timer.
int buzzInterval = 0; // to set buzzer interval

void setup() {

  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT); // call redPin GPIO_NUM_32 as output
  pinMode(YELLOW_PIN, OUTPUT); // call GPIO_NUM_33 as ouput
  pinMode(GREEN_PIN, OUTPUT); // call greenPin GPIO_NUM_25 as ouput
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set pin to input pull-up mode
  pinMode(BUZZER_PIN, OUTPUT);       // set pin to output mode

  // Initial state for states and timers.. 
  tl_state = RED_STATE;
  tl_timer = millis() + RED_MILLIS;

}
 
void loop()
{
  // TL state machine
  switch (tl_state)
  {
    case RED_STATE:
      // Turn red light on.
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);

      // Set timer for red
      tl_timer = millis() + RED_MILLIS;

      while(millis() < tl_timer){ 
        if (millis() > buzzInterval){
          tone(BUZZER_PIN, 100, 250); // buzzer on for 250ms
          buzzInterval = millis() + 500; // off for 250ms
        }
      }
      
      // move onto red yellow state
      tl_state = RED_YELLOW_STATE;
      break;

    case RED_YELLOW_STATE:
      // Turn red & yellow light on.
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);

      tl_timer = millis() + RED_YELLOW_MILLIS; // set timer for red yellow state
      delay(RED_YELLOW_MILLIS); // wait for 2 seconds
      tl_state = GREEN_STATE; // move to green state
      break; 

    case YELLOW_STATE:
      // Curn yellow light on.
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);

      if (millis() > tl_timer) 
      {
        digitalWrite(YELLOW_PIN, LOW);
        tl_timer = millis() + RED_MILLIS; // set timer for red 5sec
        tl_state = RED_STATE; // move to red state
      }
      break;

    case GREEN_STATE:
      
      // Turn green light on.
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);

      //Button is NOT pressed
      while(digitalRead(BUTTON_PIN) == LOW){
        tone(BUZZER_PIN, 200, 500); // buzzer on for 500ms
        noTone(BUZZER_PIN); // buzzer off
        delay(1500); // wait for 1500ms
      }

      //Button is pressed
      if (digitalRead(BUTTON_PIN) == HIGH)
      {
        // Turn on green for 5 seconds.
        tl_timer = millis() + GREEN_MILLIS;

        while(millis() < tl_timer){
          if (millis() > buzzInterval){
          tone(BUZZER_PIN, 300, 500); // buzzer on for 500ms
          buzzInterval = millis() + 2000; // off for 1500ms
          }
        }
        // Then move to yellow state.
        tl_timer = millis() + YELLOW_MILLIS; // Set timer for red state
        tl_state = YELLOW_STATE; // move to yellow state
      }
      break;
  }
}