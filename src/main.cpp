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
int buzzInterval = 0;

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
      tl_timer = millis() + RED_MILLIS;

      while(millis() < tl_timer){ 
        if (millis() > buzzInterval){
          tone(BUZZER_PIN, 100, 250);
          buzzInterval = millis() + 500;
        }
      }
      
      tl_state = RED_YELLOW_STATE;
      break;

    case RED_YELLOW_STATE:
      // Turn red & yellow light on.
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);

      tl_timer = millis() + RED_YELLOW_MILLIS;
      delay(RED_YELLOW_MILLIS);
      tl_state = GREEN_STATE;
      break; 

    case YELLOW_STATE:
      // Curn yellow light on.
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);

      if (millis() > tl_timer) // Set timer for red state.
      {
        digitalWrite(YELLOW_PIN, LOW);
        tl_timer = millis() + RED_MILLIS;
        tl_state = RED_STATE;
      }
      break;

    case GREEN_STATE:
      
      // Turn green light on.
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);

      while(digitalRead(BUTTON_PIN) == LOW){
        tone(BUZZER_PIN, 200, 500);
        noTone(BUZZER_PIN);
        delay(1500);
      }

      //Button is pressed
      if (digitalRead(BUTTON_PIN) == HIGH)
      {
        // Turn on green for 5 seconds.
        tl_timer = millis() + GREEN_MILLIS;
        while(millis() < tl_timer){
          if (millis() > buzzInterval){
          tone(BUZZER_PIN, 300, 250);
          buzzInterval = millis() + 2000;
          }
        }
        // Then move to yellow state.
        tl_timer = millis() + YELLOW_MILLIS;
        tl_state = YELLOW_STATE;
      }
      break;
  }

}