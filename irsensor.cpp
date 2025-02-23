#include <IRremoteESP8266.h>
#include <IRrecv.h>

const uint16_t RECV_PIN = 15;  // IR receiver connected to GPIO 15
IRrecv irrecv(RECV_PIN);       // Create an IR receiver object
decode_results results;        // Store received IR data

void setup() {
  Serial.begin(115200);  // Initialize serial monitor
  irrecv.enableIRIn();   // Start the IR receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("IR Code received: ");
    Serial.println(results.value, HEX);  // Print the received IR code in hexadecimal format
    irrecv.resume();  // Prepare for next signal
  }
}
