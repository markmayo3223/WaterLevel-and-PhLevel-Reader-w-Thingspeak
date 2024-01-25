#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define TRIGGER_PIN D5
#define ECHO_PIN D6
#define FIELD_NUM 2
#define INTERVAL_SEC 30

const char* ssid = "Wonderful";
const char* password = "Makemelaugh1";
const char* server = "api.thingspeak.com";
const char* apiKey = "VJJR6X649XP3TUQW";

WiFiClient client;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  ThingSpeak.begin(client);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  float distance = measureDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  ThingSpeak.setField(FIELD_NUM, String(distance));
  
  int status = ThingSpeak.writeFields(0, apiKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
  
  delay(INTERVAL_SEC * 1000);
}

float measureDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
