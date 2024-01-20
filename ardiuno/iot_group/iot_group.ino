#include "WiFiS3.h"

// TODO: 本来は別ファイルに書くのが良いがベタで書いている
// TODO: WifiのSSIDとPASSを記載
#define SECRET_SSID ""
#define SECRET_PASS ""

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// http://192.168.143.183/
IPAddress server(192,168,2,107);  // numeric IP　(no DNS)
// char server[] = "example.com";    // name address (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

/* -------------------------------------------------------------------------- */
void setup() {
/* -------------------------------------------------------------------------- */  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port
  }
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
     
    // wait 10 seconds for connection:
    delay(10000);
  }
  
  printWifiStatus();
}

/* just wrap the received data up to 80 columns in the serial print*/
/* -------------------------------------------------------------------------- */
void read_response() {
/* -------------------------------------------------------------------------- */  
  uint32_t received_data_num = 0;
  while (client.available()) {
    /* actual data reception */
    char c = client.read();
    /* print data to serial port */
    Serial.print(c);
    /* wrap data to 80 columns*/
    received_data_num++;
    if(received_data_num % 80 == 0) { 
      Serial.println();
    }
  }  
}

// デバッグ用に初回のみリクエストを送る
bool is_init = true;

/* -------------------------------------------------------------------------- */
void loop() {
/* -------------------------------------------------------------------------- */  
  // TODO: 席の状態が変わったら発火する
  if (is_init) {
    // デバッグ用に初回のみリクエストを送る
    is_init = false;
    updateChairStatus("1", "0");
  }
}

void updateChairStatus(String chair_id, String is_used){
  updatRequest("1", "0");
  while (true) {
    read_response();
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
      // リクエスト完了
      return;
    } 
  }
}

void updatRequest(String chair_id, String is_used) {
  Serial.println("\nStarting connection to server...");
  String path = "/chair?charNo=" + chair_id + "&is_used=" + is_used;
  // if you get a connection, report back via serial:
  if (client.connect(server, 3000)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /posts HTTP/1.1");
    client.println("Host: 192.168.2.107");
    client.println("Connection: close");
    client.println();
  }
}

/* -------------------------------------------------------------------------- */
void printWifiStatus() {
/* -------------------------------------------------------------------------- */  
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
