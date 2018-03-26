#include <ESP8266WiFi.h> //Includes the ESP8266 library ESP8266WiFi.h.

#define LED_PIN 16

//Creates the instance "server" (global) of the class "WiFiServer" listening on port 80. 
WiFiServer server(80); //Initialize the server on Port 80


// http://www.instructables.com/id/Programming-a-HTTP-Server-on-ESP-8266-12E/


void setup() {

//Set the mode of our ESP8266 to be an Access Point (AP).
WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 

//Provide the SSID and password. The password / passphrase has to be at least 8 characters long.
WiFi.softAP("Loading...12", "12345678"); // Provide the (SSID, password); . 

//Fire-up our server by calling the begin() method.
server.begin(); // Start the HTTP Server


//Looking under the hood
Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
IPAddress HTTPS_ServerIP = WiFi.softAPIP(); // Obtain the IP of the Server 
Serial.println("");
Serial.print("Server IP is: "); // Print the IP to the monitor window 
Serial.println(HTTPS_ServerIP);
Serial.println("Hello world");

/*
 * Firstly initialize the digital port GPIO16 as an output port and keep the initial state of the LED ON. 
 */
pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
//digitalWrite(LED_PIN, LOW); //Initial state is ON
digitalWrite(LED_PIN, HIGH); //Initial state is OFF
}


void loop(){

    /*
     * check if client (brower) has connected to the esp8266
     * if a browser has connected then do something 
     * else jump out and check again. we do this endlessly.
     * 
     */
    
    WiFiClient client = server.available();
    if (!client) { 
    return; 
    } 
    //Looking under the hood 
    Serial.println("Somebody has connected :)");
    //connect to network and go to  http://192.168.4.1 to see someone has connected 
  

    /*
     * The web browser connects to the HTTP server and sends the request. 
     * The server receives the request and does something with it. 
     */
    
    //Read what the browser has sent into a String class and print the request to the monitor

    //this displays all the request line code 
    //String request = client.readString(); 

    /*
    POST and GET are two HTTP request methods. 
    GET is usually intended to retrieve some data, and is expected to be idempotent
    */
    
    //this displays only the GET request and type (here it's a GET / PARAM request)
    String request = client.readStringUntil('\r'); //only the first line of the request statement 


    
    //Looking under the hood: actually printing it 
    Serial.println(request);
    //go to  http://192.168.4.1/PARAM to see the request being printed 



    /*
     * We are ready to turn the LED on GPIO16 ON/OFF through commands given via the web browser.
     */

    // Handle the Request
    
    if (request.indexOf("/OFF") != -1){ 
        digitalWrite(LED_PIN, HIGH); }
        else if (request.indexOf("/ON") != -1){ 
        digitalWrite(LED_PIN, LOW); 
        }
    /*
     * In the address bar of your browse type the following URL:
     * http://192.168.4.1/OFF
     * The LED on the ESP8266-E12 will turn OFF.
     * Then type the following URL: 
     * http://192.168.4.1/ON
     * The LED on the ESP8266-E12 will turn ON.
     */


     // Prepare the HTML document to respond and add buttons:
    
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: text/html\r\n\r\n";
    s += "<!DOCTYPE HTML> \r\n<html>\r\n";

    //create button 1, hyperlinks to /ON 
    s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
    s += "<br><br><br>";

    //create button 2, hyperlinks to /OFF
    s += "<input type=\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
    s += "</html>\n";
    
    
    //Serve the HTML document to the browser.
    
    client.flush(); //clear previous info in the stream 
    client.print(s); // Send the response to the client 
    delay(1); 
    Serial.println("Client disonnected"); //Looking under the hood
        

    
}
  


