#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif
#include "DHT.h"
// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
/*Put your SSID & Password*/
const char* ssid = "XoXo";  // SSID
const char* password = "muhachort"; // пароль
#ifdef ESP8266
// Web интерфейс для устройства
ESP8266WebServer server(80);
// DHT Sensor
uint8_t DHTPin = D4; 
#else
WebServer server(80);
// DHT Sensor
uint8_t DHTPin = 4; 
 #endif              
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                
float Temperature;
float Humidity;
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(DHTPin, INPUT);
  dht.begin();              
  Serial.println("Connecting to ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}
void handle_OnConnect() {
 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr +="<title>Информация о температуре</title>\n";
  ptr +="<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr +="body{margin-top: 50px;}\n";
  ptr +="h1 {margin: 50px auto 30px;}\n";
  ptr +="h3 {margin: 50px auto 30px;}\n";
  ptr +=".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr +=".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  ptr +=".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".humidity{font-weight: 300;font-size: 60px;color: #3498db;text-align: right;}\n";
  ptr +=".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr +=".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr +=".data{padding: 10px;}\n";
  ptr +="</style>\n";
  ptr +="<meta http-equiv=\"refresh\" content=\"2\" >\n";
  ptr +="<script>\n";
  ptr +="setInterval(loadDoc,200);\n";
  ptr +="function loadDoc() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  ptr +="};\n";
  ptr +="xhttp.open(\"GET\", \"/\", true);\n";
  ptr +="xhttp.send();\n";
  ptr +="}\n";
  ptr +="</script>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
   ptr +="<div id=\"webpage\">\n";
   #ifdef ESP8266
   ptr +="<h1>Информация о температуре в кабинете робототехники:</h1>\n";
   #else
   ptr +="<h1>Информация о температуре в кабинете робототехники:</h1>\n";
   #endif
   
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side temperature-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
   ptr +="width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
   ptr +="c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
   ptr +="c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
   ptr +="c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
   ptr +="c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side temperature-text\">Температура</div>\n";
   ptr +="<div class=\"side-by-side temperature\">";
   ptr +=(int)Temperaturestat;
   ptr +="<span class=\"superscript\">°C</span></div>\n";
   ptr +="</div>\n";
   
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side humidity-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
   ptr +="c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side humidity-text\">Влажность</div>\n";
   ptr +="<div class=\"side-by-side humidity\">";
   ptr +=(int)Humiditystat;
   ptr +="<span class=\"superscript\">%</span></div>\n";

   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side temperature-icon\">\n";
   ptr +="<svg width=\"22px\" height=\"22px\" viewBox=\"0 0 1024 1024\" class=\"icon\"  version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M513.311597 95.397443c-156.598141 0-253.554962 137.570256-253.554962 265.040908 0 105.370087 44.014782 155.726815 82.912186 200.192106l7.377094 8.41429c20.519686 23.753116 25.437407 101.224375 22.39442 158.053082a25.298159 25.298159 0 0 0 6.79655 18.445294c4.725231 4.920793 11.19721 7.767194 18.057242 7.767194h8.122482v115.854673c0 13.722111 11.134753 24.853792 24.853793 24.853792h58.187403v9.967524c0 13.719039 11.130657 24.853792 24.853792 24.853792s24.853792-11.134753 24.853792-24.853792v-9.967524h58.283649c13.722111 0 24.853792-11.131681 24.853792-24.853792V753.310317h8.155247c6.860032 0 13.332011-2.846401 18.057241-7.767194a25.293039 25.293039 0 0 0 6.796551-18.445294c-3.041963-56.828707 1.875758-134.299966 22.39442-158.053082l7.442622-8.546371c38.831875-44.398739 82.845633-94.752396 82.845634-200.060025 0.001024-127.470651-96.954773-265.040907-253.682948-265.040908z\" fill=\"#27323A\" />\n";
   ptr +="<path d=\"M571.595245 844.311197H455.124194v-91.00088h116.471051v91.00088z\" fill=\"#79CCBF\" /><path d=\"M646.740237 527.812885l-7.638184 8.705073c-30.355128 35.176604-35.404931 104.432208-35.404931 155.239445 0 4.467212 0.12901 7.896204 0.195562 11.843282H422.827779c0.066553-3.947078 0.195562-7.37607 0.195562-11.843282 0-50.87379-5.049802-120.063865-35.372166-155.239445 0-0.032764-7.571632-8.639544-7.571632-8.639544-36.310045-41.552338-70.614299-80.774313-70.614299-167.441087 0-105.85336 76.244645-215.333323 203.847377-215.333323 127.731742 0 203.976387 109.478938 203.976387 215.333323-0.001024 86.601245-34.238725 125.824244-70.548771 167.375558z\" fill=\"#F4CE73\" /><path d=\"M460.237477 205.622794c3.496568 8.476747-0.517062 18.186251-8.993808 21.68282-42.134929 17.473627-61.196602 49.383013-69.739901 73.069576-13.917673 38.642456-10.163086 84.691699 10.160014 123.168285 4.27165 8.09279 1.166205 18.123794-6.925561 22.39442-8.088694 4.27165-18.123794 1.166205-22.39442-6.92556-24.916249-47.311693-29.317932-101.907306-12.035771-149.897836 15.336778-42.361208 46.665621-75.207449 88.247652-92.426128 8.479818-3.492473 18.189323 0.520134 21.681795 8.934423z\" fill=\"#FFFFFF\" /></svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side temperature-text\">Свет</div>\n";
   ptr +="<div class=\"side-by-side temperature\">";
   ptr +=(int)Humiditystat;
   ptr +="<span class=\"superscript\">%</span></div>\n";  
   ptr +="</div>\n";

   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side humidity-icon\">\n";
   
   ptr +="<svg fill=\"#000000\" height=\"30px\" width=\"22px\" version=\"1.1\" id=\"Capa_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n";
   ptr +="viewBox=\"0 0 490 490\" xml:space=\"preserve\">\n";
   ptr +="<g>\n";
   ptr +="<g>\n";
   ptr +="<g>\n";
   ptr +="<path d=\"M470,360.75h-79.6c-8.1,0-15.4-4.8-18.5-12.3c-3.1-7.4-1.5-16,4.2-21.8l59.2-60.2c1.1-1.7,2.2-4.2,2.2-7.4\n";
   ptr +="c0-7.5-6.1-13.6-13.6-13.6s-13.6,6.1-13.6,13.6c0,11.1-9,20-20,20c-11.1,0-20-9-20-20c0-29.6,24.1-53.6,53.6-53.6\n";
   ptr +="s53.6,24.1,53.6,53.6c0,11.8-3.8,23.1-10.9,32.5c-0.5,0.7-1.1,1.3-1.7,1.9l-26.8,27.2H470c11.1,0,20,9,20,20\n";
   ptr +="C490,351.85,481.1,360.75,470,360.75z\"/>\n";
   ptr +="</g>\n";
   ptr +="<g>\n";
   ptr +="<path d=\"M271.8,321.75c-53.1,0-96.2-43.2-96.2-96.2c0-53.1,43.2-96.2,96.2-96.2c53.1,0,96.2,43.2,96.2,96.2\n";
   ptr +="S324.9,321.75,271.8,321.75z M271.8,169.35c-31,0-56.2,25.2-56.2,56.2s25.2,56.2,56.2,56.2s56.2-25.2,56.2-56.2\n";
   ptr +="C328,194.55,302.8,169.35,271.8,169.35z\"/>\n";
   ptr +="</g>\n";
   ptr +="<g>\n";
   ptr +="<path d=\"M94.3,317.85c-52,0-94.3-42.3-94.3-94.3s42.3-94.3,94.3-94.3c29.8,0,58.1,14.3,75.8,38.3c6.6,8.9,4.7,21.4-4.2,28\n";
   ptr +="s-21.4,4.7-28-4.2c-10.4-14-26.3-22-43.6-22c-29.9,0-54.2,24.3-54.2,54.2s24.3,54.2,54.2,54.2c15.3,0,29.5-6.2,39.9-17.5\n";
   ptr +="c7.5-8.1,20.2-8.7,28.3-1.2c8.1,7.5,8.7,20.2,1.2,28.3C145.8,306.75,120.6,317.85,94.3,317.85z\"/>\n";
   ptr +="</g>\n";
   ptr +="</g>\n";
   ptr +="</g>\n";
   ptr +="</svg>\n";
   
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side humidity-text\">CO2</div>\n";
   ptr +="<div class=\"side-by-side humidity\">";
   ptr +=(int)Humiditystat;
   ptr +="<span class=\"superscript\">%</span></div>\n";
   
   ptr +="<h3>© Nazgul chort Adilet boss</h3>\n";
   ptr +="</div>\n";
  ptr +="</div>\n";
 
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
