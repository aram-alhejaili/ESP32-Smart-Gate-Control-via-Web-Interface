#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const int greenLED = 4;
const int redLED = 5;
const int servoPin = 18;

const char* ssid = "Aram-ESP32-Control";
const char* password = "12345678";

Servo myServo;
WebServer server(80);

String page() {
  return R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Servo Control</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      padding-top: 60px;
    }

    button {
      width: 160px;
      height: 60px;
      margin: 15px;
      font-size: 22px;
      border: none;
      border-radius: 10px;
      color: white;
      cursor: pointer;
    }

    .open {
      background-color: green;
    }

    .close {
      background-color: red;
    }
  </style>
</head>
<body>
  <h1>Servo Motor Control</h1>
  <a href="/open"><button class="open">Open</button></a>
  <a href="/close"><button class="close">Close</button></a>
</body>
</html>
)rawliteral";
}

void handleRoot() {
  server.send(200, "text/html", page());
}

void handleOpen() {
  myServo.write(90);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  server.send(200, "text/html", page());
}

void handleClose() {
  myServo.write(0);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  server.send(200, "text/html", page());
}

void setup() {
  Serial.begin(115200);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  myServo.attach(servoPin);

  myServo.write(0);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);

  WiFi.softAP(ssid, password);

  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);

  server.begin();
}

void loop() {
  server.handleClient();
}










