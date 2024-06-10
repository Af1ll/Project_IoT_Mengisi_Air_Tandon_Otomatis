#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13
const int trigPin = 7; // Pin Trig terhubung ke pin 9 pada Arduino
const int echoPin = 6; // Pin Echo terhubung ke pin 10 pada Arduino

Servo myServo;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(11);
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float speedOfSound = 331.3 + 0.606 * temperatureC;
  
  // Mengirim sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Mengukur durasi pantulan sinyal ultrasonik
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2.0) * (speedOfSound / 10000.0);
  
  // Menampilkan suhu dan jarak di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(temperatureC);
  Serial.print(" °C, Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Menggerakkan servo berdasarkan jarak yang terukur
  if (distance >= 390) { // Ubah sesuai dengan kebutuhan
    myServo.write(180);
  }
  else if (distance <= 30) { // Ubah sesuai dengan kebutuhan
    myServo.write(0);
  }
  else {
    myServo.write(90);
  }

  // Menunggu servo mencapai posisi
  delay(500);

  // Menunggu sebelum mengulangi loop
  delay(1000);
}