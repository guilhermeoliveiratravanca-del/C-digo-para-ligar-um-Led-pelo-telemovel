#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

WiFiServer server(80);
const int pinoLED= 2;

 void setup(){
	pinMode(pinoLED, OUTPUT);
    Serial.begin(115200);
	WiFi.softAP("LED","12120078");
	Serial.print("IP: ");
	Serial.println(WiFi.softAPIP());
	server.begin();
 }
 
 void loop (){
     WiFiClient client = server.available();
	 if(client) {
		 String HTTP_req ="";
		 while(client.connected()){
			 if(client.available()){
				 char c = client.read();
				 HTTP_req +=c;
				 
				 if (c == '\n') {
					 client.println("HTTP/1.1 200 OK"); //obrigatorio para o site cabeçalho 
					 client.println("Content-type:text/html");
					 client.println("Connection: close");
					 client.println();
					 
					 client.println("<!DOCTYPE html><html>");
					 client.println("<body>");
					 client.println("<h1>Controlo de Led</h1>");
		 
					 client.println("<p><a href=\"/LIGAR\"><button>LIGAR</button></a></p>");
					 client.println("<p><a href=\"/DESLIGAR\"><button>DESLIGAR</button></a></p>");
		 
					 client.println("</body></html>");
					 break;
				 }
			 }
		 }
	 
	 
		 if (HTTP_req.indexOf("GET /LIGAR") >= 0){
			   Serial.println("Ligou");
			   digitalWrite(pinoLED, HIGH);
		 }
		 if (HTTP_req.indexOf("GET /DESLIGAR") >= 0) {
			   Serial.println("Desligou");
			   digitalWrite(pinoLED, LOW);
		 }
		 client.stop();
	 }
 }


