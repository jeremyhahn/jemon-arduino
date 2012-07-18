/**
 * Arduino HTTP client
 * 
 * @author Jeremy Hahn
 * @copyright Make A Byte, inc
 */
#include "Arduino.h"
#include "JEMonAPI.h"

/**
 * Constructor
 */
JEMonAPI::JEMonAPI(int ethernetPin, int sdcardPin, uint8_t *ip, uint16_t port) {

    // Enable ethernet, disable SD card
    pinMode(ethernetPin, OUTPUT);
    pinMode(sdcardPin, OUTPUT);
    digitalWrite(sdcardPin, HIGH);

    _ethernetPin = ethernetPin;
    _sdcardPin = sdcardPin;
    _ip = ip;
    _port = port;
}

/**
 * Destructor
 */
JEMonAPI::~JEMonAPI() {

   Serial.println("[~JEMonAPI] Destroyed...");
}

/**
 * Connects to the remote server
 *
 * @private
 */
boolean JEMonAPI::connect() {

    if(_client.connected()) return true;

    Serial.print("[JEMonAPI.connect] Connecting to server ");
    Serial.print(_ip[0]);
    Serial.print(".");
    Serial.print(_ip[1]);
    Serial.print(".");
    Serial.print(_ip[2]);
    Serial.print(".");
    Serial.print(_ip[3]);
    Serial.print(":");
    Serial.println(_port);

    return _client.connect(_ip, _port);
}

/**
 * Boolean connection flag
 *
 * @public
 */
boolean JEMonAPI::connected() {
   return _client.connected();
}

/**
 * Performs an HTTP GET request against the specified resource
 *
 * @public
 */
String JEMonAPI::get(char *resource) {

     Serial.print("[JEMonAPI.get] Resource: ");
     Serial.println(resource);

     String response = String("");

     if(connect()) {

        Serial.println("[JEMonAPI.get] Connected, sending GET request");

        _client.print("GET ");
        _client.print(resource);
        _client.println(" HTTP/1.0");
        _client.println("Host: energy-monitor");
        _client.println("User-Agent: JEMon 0.1a / Arduino 1.0");
        _client.println("Connection: close");
        _client.println();

        while(_client.connected()) {

            if(_client.available()) {

               char c = _client.read();
               response += c;
            }
        }
     }
     else {
         Serial.println("[JEMonAPI.get] Connection failed");
     }

     _client.stop();
     _client.flush();

     Serial.println("[JEMonAPI.get] Response: ");
     Serial.println("");
     Serial.println(response);

     return response;
}

/**
 * Performs an HTTP POST request against the specified resource
 *
 * @public
 */
String JEMonAPI::post(char *resource, char *params) {

     Serial.print("[JEMonAPI.post] resource: ");
     Serial.println(resource);
//     Serial.print(", params: ");
//     Serial.println(params);

     String response = String("");

     if(connect()) {

        Serial.println("[API.post] Connected, sending POST request");

        _client.print("POST ");
        _client.print(resource);
        _client.println(" HTTP/1.0");
        _client.println("Host: energy-monitor");
        _client.println("User-Agent: JEMon 0.1a / Arduino 1.0");
        _client.println("Connection: close");
        _client.println("Content-Type: application/x-www-form-urlencoded");
        _client.print("Content-Length: ");
        _client.println(strlen(params));
        _client.println();
        _client.println(params);

        while(_client.connected()) {

            if(_client.available()) {

               char c = _client.read();
               response += c;
            }
        }
     }
     else {
         Serial.println("[JEMonAPI.post] Connection failed");
     }

     _client.stop();
     _client.flush();

     Serial.println("[JEMonAPI.post] Response: ");
     Serial.println("");
     Serial.println(response);

     return response;
}
