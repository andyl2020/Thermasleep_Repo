

/*
 * from: https://github.com/acrobotic/Ai_Tips_ESP8266/blob/master/wifi_modes/wifi_modes.ino
 * 
 * the aim of this code is to grab data from a weather station online and display it. 
 * using: https://www.youtube.com/watch?v=8xqgdXvn3yw
 * 
 * the website it is grabbing data from is: https://www.wunderground.com/
 * email: luundy@yahoo.ca
 * pass: the simpliest one 
 * 
 * 
 * to access the data we want to pull: api.wunderground.com/api/YOUR_API_KEY/conditions/q/Canada/Vancouver.json
 * with api key being: 93046f7ee9e1ae93
 * 
 * 
 * http://api.wunderground.com/api/93046f7ee9e1ae93/conditions/q/Canada/Vancouver.json
 */

/*
 * make sure you have these installed 
 */
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>
#include <ArduinoJson.h> //since the response request is going to be in JSON

ESP8266WebServer server;
uint8_t pin_led = 16;
char* ssid = "AcroboticGuest";
char* password = "13meetup37";
char* mySsid = "AcroboticGuest2";

/*
 * constants for weather-ing
 */

#define WU_API_KEY "93046f7ee9e1ae93" //your api key from earlier  
#define WU_LOCATION "Vancouver/Canada"
#define WU_URL "api.wunderground.com"

//define char array that won't change to hold JSON data (response buffer)
static char respBuffer[4096]; //give it a lot of space 





/*
IPAddress ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);
*/
void setup()
{
  pinMode(pin_led, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid,password);
  Serial.begin(115200); //check to see if this matches ur baud rate 
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle",toggleLED); 
  /*
   * add one more route to our server:
   * this will add another 'link' to our main website that will run function
   * getData which will ask to grab the data and do it 
   */
  server.on("/getdata",getData); 
  
  server.begin();

  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(mySsid, password);
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}

/*
 * create a wifi client object
 */

 WifiClient client; 




/*
 * here is our function for grabbing weather data!
 * 
 */

void getData()
{
  //build request that will be sent our from the server from the esp (client)
  const char request[] =
    //method used (GET), path, and url *** and then the version of HTTP that we're using 
    "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"

    //define user
    "User-Agent: ESP8266/0.1\r\n"

    //accepts everything from everywhere
    "Accept: */*\r\n"

    "Host: "WU_URL "\r\n"
    
    //close the connection when the request is over
    "Connection: close\r\n"
    
    //end overall:
    "\r\n";

    //let's visualize all this on the serial print monitor
    Serial.println(request);

    //use client object to connect to the server on port 80 (default port)
    client.connect(WU_URL, 80);
    //send our request
    client.print(request); 
    //flush out communication between the client and the server
    client.flush();
    //give the server some time to respond:
    delay(1000); 


    //declare the index as a 16 bit unsigned integer
    uint16_t index = 0;
    
    //use connected method of server to check if we connected 
    while(client.connected())
      {
        //if it is connected, use the available method to process any data that's in the response

        if(client.available())
        {
          //process data by putting it into our response buffer
          //use the read method to access the data we stored
          respBuffer[index++] = client.read();
          //add a delay betwen reads
          delay(1);
        }
      }
    client.stop();

    /*
     * the response is going to give us a bunch of things we don't want
     * so in order to solve this, find { and } with the data we want in between
     * to avoid grabbing data 
     * 
     */

     //returns a character pointer we'll call jason 
     char * json = strchr(respBuffer = '{');

    //parse the data that's in our data string json, using arduino json library
    //use dynamic json buffer b/c a static one creates problems due to the large size of the data

    DynamicJsonBuffer jBuffer; 

    //to attract the data we want, use the parseobject method 
    JsonObject& root = jBuffer.parseObject(json);

    //everything we want starts at 'current observation'
    JsonObject& current = root["current_observation"];

      
    
}


















 
