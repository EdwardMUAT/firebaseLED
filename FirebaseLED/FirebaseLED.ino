#include <M5StickCPlus.h>
#include <ArduinoJson.h>
#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>
#include "secrets.h"

#define pinMode
#define BUILTIN_LED 10

String fireStatus; // Declare fireStatus variable

void setup() {
  Serial.begin(115200);
  while (!Serial){};

  //wifi stuff
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("Connecting to: ");
  Serial.println(SECRET_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected!");

  // Set the pin mode
  pinMode(BUILTIN_LED, OUTPUT);

  //firebase stuff
  Firebase.begin(host, firebaseAuth);
  Serial.println("Firebase initialized!");
  
  // Set initial LED status to "OFF"
  Firebase.setString("LED_Status", "OFF");
  Serial.println("LED_Status set to OFF");
}

void loop() {
  // Get LED status from Firebase
  fireStatus = Firebase.getString("LED_Status");
  Serial.print("LED_Status received from Firebase: ");
  Serial.println(fireStatus);

  // Logic to control LED based on the status received from Firebase
  if (fireStatus == "OFF") {
    Serial.println("Turning LED off");
    digitalWrite(BUILTIN_LED, HIGH);
  } else if (fireStatus == "ON") {
    Serial.println("Turning LED on");
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    Serial.println("Wrong credentials received from Firebase, please use ON/OFF");
  }

  delay(1000); // Add a delay to avoid rapid Firebase requests
}
