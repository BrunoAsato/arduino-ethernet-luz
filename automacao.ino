#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x09, 0xA7 }; //physical mac address
byte ip[] = { 192, 168, 0, 99 }; // ip in lan
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

int pin = 9; 
boolean ligado = true;

//////////////////////

void setup(){

  pinMode(pin, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("Asato Remote Automation V1"); 
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging
          if(readString.indexOf("?ligar") >0)//checks for on
          {
            digitalWrite(pin, HIGH);    // set pin 4 high
            Serial.println("On");
            ligado = false;
          }
          else{
            if(readString.indexOf("?desligar") >0)//checks for off
            {
              digitalWrite(pin, LOW);    // set pin 4 low
              Serial.println("Off");
              ligado = true;
            }
          }
          //clearing string for next read
          readString="";


          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<html>");
          client.println("<head>");
          client.println("<title>Asato - Remote Automation</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<link rel='stylesheet' type='text/css' href='http://www.skycore.com.br/assets/bootstrap/css/bootstrap.min.css' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://www.skycore.com.br/automacao/style.css' />");
          client.println("<script type='text/javascript' src='http://www.skycore.com.br/automacao/script.js'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div id='wrapper'>Asato Remote Automation V1");
          client.print("<div id='rele'></div><div id='estado' style='visibility: hidden;'>");
          client.print(ligado);
          client.println("</div>");
          client.println("<div id='botao'></div>");
          client.println("</div>");
          client.println("<script>AlteraEstadoRele()</script>");
          client.println("</body>");
          client.println("</head>");

          delay(1);
          //stopping client
          client.stop();



        }
      }
    }
  }
}