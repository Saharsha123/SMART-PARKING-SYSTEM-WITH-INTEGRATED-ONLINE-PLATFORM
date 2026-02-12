#include <WiFi.h>
#include <Firebase_ESP_Client.h>
const char* ssid = "YOUR_WIFI_SSID"
const char* password = "YOUR_WIFI_PASSWORD"
#define FIREBASE_HOST "YOUR_FIREBASE_URL"
#define FIREBASE_AUTH "YOUR_FIREBASE_KEY"
// Creating Firebase Config and Authentication objects
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;
FirebaseData firebaseData;
//Bike Parking Sensors
const int bikeTrigPins[] = {15, 4};
const int bikeEchoPins[] = {2, 5};
//Car Parking Sensors
const int carTrigPins[] = {18, 21};
const int carEchoPins[] = {19, 22};
const int numBikeSensors = 2;
const int numCarSensors = 2;
const long thresholdDistance = 5;
void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");
// Setting Firebase configuration
firebaseConfig.host = FIREBASE_HOST;
firebaseConfig.api_key = FIREBASE_AUTH;
firebaseAuth.user.email = USER_EMAIL;
firebaseAuth.user.password = USER_PASSWORD;
// Initializing Firebase
Firebase.begin(&firebaseConfig, &firebaseAuth);
Serial.println("Authenticated to Firebase");
// Initializing sensor pins for bike parking
for (int i = 0; i < numBikeSensors; i++) {
pinMode(bikeTrigPins[i], OUTPUT);
pinMode(bikeEchoPins[i], INPUT);
}
// Initializing sensor pins for car parking
for (int i = 0; i < numCarSensors; i++) {
pinMode(carTrigPins[i], OUTPUT);
pinMode(carEchoPins[i], INPUT);
}
}
long measureDistance(int trigPin, int echoPin) {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH, 30000);
return (duration > 0) ? (duration / 2) / 29.1 : -1;
}
void loop() {
FirebaseJson json;
// Processing bike parking sensors
for (int i = 0; i < numBikeSensors; i++) {
delay(50); // Delay to avoid signal overlap
long distance = measureDistance(bikeTrigPins[i], bikeEchoPins[i]);
if (distance > 0) {
bool objectDetected = (distance <= thresholdDistance);
// Adding bike sensor data to JSON object
String path = "bike/B" + String(i + 1);
json.set(path + "/distance", distance);
json.set(path + "/objectDetected", objectDetected);
// Debugging logs
Serial.print("Bike Sensor B");
Serial.print(i + 1);
Serial.print(": Distance = ");
Serial.print(distance);
Serial.print(" cm, Object detected = ");
Serial.println(objectDetected ? "True" : "False");
} else {
Serial.print("Bike Sensor B");
Serial.print(i + 1);
Serial.println(": Invalid reading");
}
}
// Processing car parking sensors
for (int i = 0; i < numCarSensors; i++) {
delay(50); // Delay to avoid signal overlap
long distance = measureDistance(carTrigPins[i], carEchoPins[i]);
if (distance > 0) {
bool objectDetected = (distance <= thresholdDistance);
// Adding car sensor data to JSON object
String path = "car/C" + String(i + 1);
json.set(path + "/distance", distance);
json.set(path + "/objectDetected", objectDetected);
// Debugging logs
Serial.print("Car Sensor C");
Serial.print(i + 1);
Serial.print(": Distance = ");
Serial.print(distance);
Serial.print(" cm, Object detected = ");
Serial.println(objectDetected ? "True" : "False");
} else {
Serial.print("Car Sensor C");
Serial.print(i + 1);
Serial.println(": Invalid reading");
}
}
// Sending all sensor data to Firebase
if (Firebase.RTDB.setJSON(&firebaseData, "/ultrasonic", &json)) {
Serial.println("All sensor data sent to Firebase successfully");
} else {
Serial.print("Error sending data: ");
Serial.println(firebaseData.errorReason());
}
delay(200);// Delay between complete cycles
}