#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Arduino.h>
#include <IRsend.h>

int volumeUp = 0;
int volumeDown = 0;
int mute = 0;
int power =0;
int presses[4];

unsigned long codes[4] = {0xFF15EA,0xFF31CE,0xFF39C6,0xFF11EE};

const uint16_t RECV_PIN = 15;  // Pin where the IR sensor is connected
const uint16_t kIrLed = 2;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const int delayinterval = 170;
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

IRrecv irrecv(RECV_PIN);  // Create an IRrecv object
decode_results results;   // Create a container for the received data

unsigned long startTime = millis(); // start the sleep timer
unsigned long autoOffDuration = 3600000; // 1 hour
//unsigned long autoOffDuration = 100000;
unsigned long now; //define current time variable



void setup() {
  Serial.begin(115200);  // Start the serial communication
  irrecv.enableIRIn();   // Start the IR receiver

  irsend.begin();
  pinMode(4, INPUT); //define the power indicator pin


}

void loop() {

    // Check sleep duration
    now = millis();
    if (((now - startTime) >= autoOffDuration) && digitalRead(4) == HIGH) {
  
      Serial.println("Sleep timer reached, powering off.");
      irsend.sendNEC(0xFF15EA); // Send first power off signal
      delay(10000); // Wait 10 seconds
      irsend.sendNEC(0xFF15EA); // Send second power off signal
      startTime = millis(); // Reset sleep timer
  
      delay(5000); // Further delay to avoid errors
    }
  
    // Process received IR signal
    if (irrecv.decode(&results)) {
      Serial.print("IR Code received: ");
      Serial.println(results.value);  // Print the received IR code in hexadecimal format
  
      startTime = millis(); // Reset sleep timer
  
      // Handle IR signals 
      switch (results.value) {
        case 1086218909:  // Power
          delay(delayinterval);
          irsend.sendNEC(0xFF15EA);
          Serial.println("Sending power signal");
          presses[0]++;
          break;
  
        case 1086206159:  // Volume Up
          delay(delayinterval);
          irsend.sendNEC(0xFF31CE);
          Serial.println("Sending volume up signal");
          presses[1]++;
          break;
  
        case 1086232679:  // Volume Down
          delay(delayinterval);
          irsend.sendNEC(0xFF39C6);
          Serial.println("Sending volume down signal");
          presses[2]++;
          break;
  
        case 1086206669:  // Mute
          delay(delayinterval);
          irsend.sendNEC(0xFF11EE);
          Serial.println("Sending mute signal");
          presses[3]++;
          break;
  
        default:
          Serial.println("Sending other signal directly to projector");
          irsend.sendNEC(results.value);
          break;
      }
  
      irrecv.resume();  // Receive the next value
    }
  }
  