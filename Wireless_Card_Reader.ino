#include <ESP8266WiFi.h>
#include <SD.h>
#include "ESP8266FtpServer.h"

const char* ssid = "SDcard Reader";
const char* password = "ASDF@123";

// config static IP

IPAddress apIP(192, 168, 12,7);  
IPAddress gateway(192, 168,12, 7);
IPAddress subnet(255, 255, 255, 0); 

FtpServer ftpSrv;//set #define FTP_DEBUG in ESP8266FtpServer.h to see ftp verbose on serial

void setup(void){
  Serial.begin(115200);
  Serial.println("");
  WiFi.config(apIP, gateway, subnet);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  delay(100);
  WiFi.softAPConfig(apIP, gateway, subnet);
  WiFi.softAP(ssid, password);
  
  if (SD.begin(4)) {
      Serial.println("SD opened!");
      ftpSrv.begin("esp8266","esp8266");    //username, password for ftp.  set ports in ESP8266FtpServer.h  (default 21, 50009 for PASV)
  }   
}
void loop(void){
  ftpSrv.handleFTP();        //make sure in loop you call handleFTP()!!   
}
