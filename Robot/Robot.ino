/*
 * Arduino projekt för EEDat. 
 */
// Dessa måste finnas med i projektet.
#include "secrets.h"
#include "config.h"
// Inkludera olika bibliotek
#include "WiFiEsp.h"
#include <SoftwareSerial.h>

/**
 * Här definerar ni funktioner.
 * Lägg till funktioner och namnge dom logiskt.
 */
<<<<<<< HEAD
SoftwareSerial Serial1(6, 7);
void initPins();
void blinkStatusLed(int del);
void connectToWiFi(void);
WiFiEspServer server (8080);
=======
SoftwareSerial Serial1(SOFTSERIAL_RX, SOFTSERIAL_TX);

void initPins();
void blinkStatusLed(int del);
void connectToWiFi(void);
void motorForward(int speed);
void motorStop(void);
void motorLeft(int speed);
void motorRight(int speed);


WiFiEspServer server (SERVER_PORT);
>>>>>>> a537968068eeca8acc64988608e2f4edd693809f
 int status = WL_IDLE_STATUS;

/**
* Setup
*/
void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);

  initPins();
  connectToWiFi();
}

/**
* loop
*/
void loop()
{
    WiFiEspClient client = server.available();

  if (client) {
    Serial.println("New client");

    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);


        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");

          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<head>\r\n");
          client.print("<title>My Arduino</title>\r\n");
          client.print("</head>\r\n");
          client.print("<body>\r\n");
          client.print("<h1>Hello World!</h1>\r\n");
          client.print("<p>We're online!</p>\r\n");
          client.print("</body>\r\n");
          client.print("</html>\r\n");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
  
    delay(10);

    client.stop();
    Serial.println("Client disconnected");
  }
  blinkStatusLed(500);
}

/**
*  Alla pins som skall ha output eller input
*  Här lägger ni till de pins som ska fungera som input/output.
*/
void initPins()
{
  pinMode(STATUS_LED, OUTPUT);
}

/**
* Denna funktion används för att blink status_led som definertats i config.h
* Modifiera ej denna funktion
*/
void blinkStatusLed(int del)
{
  digitalWrite(STATUS_LED, HIGH);
  delay(del);
  digitalWrite(STATUS_LED, LOW);
  delay(del);
}

/**
* Denna funktion används för att ansluta till wifi.
*/
void connectToWiFi()
{

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true)
      ;
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID_NAME);
    WiFi.begin(SSID_NAME, SSID_PASSWORD);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();
  server.begin();
}




void printWifiStatus() {

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}
<<<<<<< HEAD
=======

void motorForward(int speed){
    digitalWrite(MOTOR_LEFT, HIGH);
    digitalWrite(MOTOR_RIGHT, HIGH);
}

void motorStop(){
  //
    digitalWrite(MOTOR_LEFT, LOW);
    digitalWrite(MOTOR_RIGHT, LOW); 
}

void motorLeft(int speed){
    digitalWrite(MOTOR_LEFT, HIGH);
    digitalWrite(MOTOR_RIGHT, LOW);
}

void motorRight(int speed){
    digitalWrite(MOTOR_LEFT, LOW);
    digitalWrite(MOTOR_RIGHT, HIGH);
}
>>>>>>> a537968068eeca8acc64988608e2f4edd693809f
