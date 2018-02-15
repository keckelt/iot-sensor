
#define DEBUG 1
// Baud Rate of 115200, just like the uplaod speed I've set here in Arduino IDE (Tools -> Upload Speed)
// DEBUG_PRINTLN = Serial.println => Appends NL & CR 

#include <Basecamp.hpp>

Basecamp iot;


const int BUTTON_PIN = 26;     // Set to INPUT_PULLUP and connect button to GND and Pin 25 (will be False if pressed)
const int LED_PIN =  25;      // Set to OUTPUT and connect Pin 35 -> 1k Ohm --> LED --> GND


void setup() {
  DEBUG_PRINTLN("Setup Pins");

  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Turn off LED
  
  // PULLLUP_INPUT = pulled up to vcc with 10-20k ohm. set to gnd with button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  DEBUG_PRINTLN("Setup IoT");
  iot.begin();

  iot.mqtt.onConnect(transmitStatus);
  iot.mqtt.onPublish(suspendESP);

  DEBUG_PRINTLN("Setup done");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW)
  { 
    DEBUG_PRINTLN("Button Pressed");
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    iot.mqtt.publish("flat/entrance/door", 1, true, "open" );

    // Check if button has been pressed
    while (digitalRead(BUTTON_PIN) == LOW)
      ; // Wait for button to be released

iot.mqtt.publish("flat/entrance/door", 1, true, "closed" );
    DEBUG_PRINTLN("Button Released");
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
}

void transmitStatus(bool sessionPresent) {
    DEBUG_PRINTLN("I AM ALIVE");
    iot.mqtt.publish("flat/entrance/status", 1, true, "alive" );
}

void suspendESP(uint16_t packetId) {
  delay(150);
  DEBUG_PRINTLN("Data published");
  
  delay(5000);
  transmitStatus(true);
}
