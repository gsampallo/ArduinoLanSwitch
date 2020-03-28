#include <EtherCard.h>

static byte mymac[] = {0xDD,0xDD,0xDD,0x00,0x01,0x05};
static byte myip[] = {192,168,2,5};
byte Ethernet::buffer[700];

const int pinSw1 = 2;
const int pinSw2 = 3;

char* estadoSw1="OFF";
char* estadoSw2="OFF";

void setup () {
 
  Serial.begin(9600);
 
  if (!ether.begin(sizeof Ethernet::buffer, mymac, 10))
    Serial.println( "No se ha podido acceder a la controlador Ethernet");
 else
   Serial.println("Controlador Ethernet inicializado");
 
  if (!ether.staticSetup(myip))
    Serial.println("No se pudo establecer la dirección IP");

  Serial.println();
  
  pinMode(pinSw1, OUTPUT);
  digitalWrite(pinSw1, HIGH);

  pinMode(pinSw2, OUTPUT);
  digitalWrite(pinSw2, HIGH);
  
}

static word homePage() {
  
 BufferFiller bfill = ether.tcpOffset();
 
 bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/htmlrnPragma: no-cachernRefresh: 5\r\n\r\n"
      "{\"uptime\":\"$L\",\"s1\":\"$S\",\"s2\":\"$S\"}"      
      ),millis()/1000,estadoSw1,estadoSw2);
     
  return bfill.position();
}
  
void loop() {
 
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if(pos) {
    // http://192.168.2.5/?status1=ON
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status1=ON") != 0) {
      Serial.println("Comando ON recivido");
      digitalWrite(pinSw1, LOW);
      estadoSw1 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status1=OFF") != 0) {
      Serial.println("Comando OFF recivido");
      digitalWrite(pinSw1, HIGH);
       estadoSw1= "OFF";
    }  

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status2=ON") != 0) {
      Serial.println("Comando ON recivido");
      digitalWrite(pinSw2, LOW);
      estadoSw2 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status2=OFF") != 0) {
      Serial.println("Comando OFF recivido");
      digitalWrite(pinSw2, HIGH);
       estadoSw2= "OFF";
    }
          
    ether.httpServerReply(homePage()); 
  }
}