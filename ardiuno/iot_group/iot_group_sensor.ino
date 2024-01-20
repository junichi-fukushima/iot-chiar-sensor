#include <HCSR04.h>

byte triggerPin = 12;
byte echoCount = 3;
byte* echoPins = new byte[echoCount] { 10, 9, 8 };
int chairNumbers[] = {1, 2, 3};

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
}

void loop () {
  double* distances = HCSR04.measureDistanceCm();

  for (int i = 0; i < echoCount; i++) {
    Serial.print("Chair: ");
    Serial.print(chairNumbers[i]);
    Serial.print(", Distance: ");
    Serial.print(distances[i]);

    if (distances[i] >= 20 && distances[i] <= 90) {
      Serial.println(", Status: 1");
    } else {
      Serial.println(", Status: 0");
    }
  }
  
  delay(250);
}