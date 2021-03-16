/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/
// Load Wi-Fi library
#include <WiFi.h>

//Load Motor Class
#include "motor.h"

//Load Robot Class
#include "robot.h"

// Replace with your network credentials
const char* ssid = "Ziggo1931E97-2.4GHz";
const char* password = "Cuuxsvdy4z7m";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Motor A
Motor motor1 = Motor(32, 22, 27, 0);
Motor motor2 = Motor(23, 19, 18, 1);
Motor motor3 = Motor(33, 2, 26, 2);
Motor motor4 = Motor(4, 16, 17, 3);  
Robot robot = Robot();

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /forward/on") >= 0) {
              Serial.println("Voorwaardsch aan");
              motor1.Rotate(Forward);
              motor2.Rotate(Forward);
              motor3.Rotate(Forward);
              motor4.Rotate(Forward);
              robot.SetMotionState(Forward, true);
            } else if (header.indexOf("GET /forward/off") >= 0) {
              Serial.println("Voorwaardsch uit");
              motor1.Stop();
              motor2.Stop();
              motor3.Stop();
              motor4.Stop();
              robot.SetMotionState(Forward, false);
            } else if (header.indexOf("GET /backward/on") >= 0) {
              motor1.Rotate(Backward);
              motor2.Rotate(Backward);
              motor3.Rotate(Backward);
              motor4.Rotate(Backward);
              robot.SetMotionState(Backward, true);
            } else if (header.indexOf("GET /backward/off") >= 0) {
              motor1.Stop();
              motor2.Stop();
              motor3.Stop();
              motor4.Stop();
              robot.SetMotionState(Backward, false);
            } else if (header.indexOf("GET /left/on") >= 0) {
              motor1.Rotate(Backward);
              motor2.Rotate(Forward);
              motor3.Rotate(Backward);
              motor4.Rotate(Forward);
              robot.SetMotionState(Left, true);
            } else if (header.indexOf("GET /left/off") >= 0) {
              motor1.Stop();
              motor2.Stop();
              motor3.Stop();
              motor4.Stop();
              robot.SetMotionState(Left, false);
            } else if (header.indexOf("GET /right/on") >= 0) {
              motor1.Rotate(Forward);
              motor2.Rotate(Backward);
              motor3.Rotate(Forward);
              motor4.Rotate(Backward);
              robot.SetMotionState(Right, true);
            } else if (header.indexOf("GET /right/off") >= 0) {
              motor1.Stop();
              motor2.Stop();
              motor3.Stop();
              motor4.Stop();
              robot.SetMotionState(Right, false);
            } 

            else if (header.indexOf("GET /tuuter/on") >= 0) {
              robot.SetMotionState(Right, false);
              robot.SetTuuterState(true);
            } else if (header.indexOf("GET /tuuter/off") >= 0) {
              robot.SetTuuterState(false);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 25  
            client.println("<p>Forward - State</p>");
            // If the output25State is off, it displays the ON button       
            if (robot.forwardState=="off") {
              client.println("<p><a href=\"/forward/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/forward/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Backward - State</p>");
            // If the output27State is off, it displays the ON button       
            if (robot.backwardState=="off") {
              client.println("<p><a href=\"/backward/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/backward/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            // Display current state, and ON/OFF buttons for GPIO 19  
            client.println("<p>Left - State</p>");
            // If the output27State is off, it displays the ON button       
            if (robot.leftState=="off") {
              client.println("<p><a href=\"/left/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/left/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 18  
            client.println("<p>Right - State</p>");
            // If the output27State is off, it displays the ON button       
            if (robot.rightState=="off") {
              client.println("<p><a href=\"/right/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/right/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>Tuuter - State</p>");
            // If the output27State is off, it displays the ON button       
            if (robot.tuuterState =="off") {
              client.println("<p><a href=\"/tuuter/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/tuuter/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
