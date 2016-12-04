

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "OnePlus3"; 
char pass[] = "12345678"; 
int keyIndex = 0;            

int status = WL_IDLE_STATUS;
char state = 'k';
char laststate = 'k';
IPAddress server(188,166,150,44);  //my super sexy ip adress

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 300;  // delay between updates, in milliseconds


WiFiClient client;
//================================================ Setup ===============================
void setup() {
  pinMode(8, OUTPUT);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  
 
}
//======================================================================== Main Loop starts ==============================================
void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
  //============================= Read Output ========
  while (client.available()) {
   
    char c = client.read();
    //Serial.write(c);
    // ============== see if this is a usable state
    if(c == '0' || c == '1'){
      state = c;
    }
    //Serial.println("Boobs");
  }
  //======================== if to stop serial spamm
  if (state != laststate){
    Serial.println(state);
    laststate = state;
  }
  //======================== set relay to state
  if(state == '0'){
    digitalWrite(8, LOW);
  }
  else{
    digitalWrite(8, HIGH);
  }
  if (!client.connected() && lastConnected) {
    Serial.println();
    //Serial.println("disconnecting.");
    client.stop();
  }
      if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
      httpRequest();
    }
    // store the state of the connection for next time through
    // the loop:
    lastConnected = client.connected();
  }


// ======================================================= Print Status of wifi ==============
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//========================================================= Http Request ========================
void httpRequest() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    //Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /tesla/stat.txt HTTP/1.1");
    client.println("Host: www.kristofer.is");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}



