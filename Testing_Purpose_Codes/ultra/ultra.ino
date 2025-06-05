#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h> // instead of FirebaseESP8266.h

#include <NewPing.h>

// WiFi credentials
#define WIFI_SSID "Dialog 4G 425"
#define WIFI_PASSWORD "C1fac8e3"

// Firebase credentials
#define FIREBASE_HOST "ultraesp-7f995-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "emjo3bgwUMlcYnHSXF2DNzeoqhfnjOnhxdmOflZY"

// Ultrasonic Sensor Pins
#define TRIG_PIN D2
#define ECHO_PIN D1
#define MAX_DISTANCE 400

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected");

  // Firebase config
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  delay(1000);
  int distance = sonar.ping_cm();
  if (distance == 0)
    distance = -1;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (Firebase.setInt(fbdo, "/sensor/distance", distance))
  {
    Serial.println("Sent to Firebase");
  }
  else
  {
    Serial.print("Firebase error: ");
    Serial.println(fbdo.errorReason());
  }
}
