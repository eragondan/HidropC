#include <DHT.h>
#include <Servo.h>
#define BOMBA 11  //Se definen las constantes que refieren al pin de arduino para el cual corresponden.
#define VENTI 10
#define FOCO 9
#define LED 8
#define SRVVENTW 7
#define SRVPUERW 6
#define SRVVENTE 5
#define SRVPUERE 4
#define DHTPINW 3
#define DHTPINE 2
#define DHTTYPE DHT11
Servo seventw, sevente, sepuerw, sepuere;//Se inicializan dos tipos de objeto servomotor.
DHT dhtw(DHTPINW, DHTTYPE);//Se especifica que se usara un sensor DTH11.
DHT dhte(DHTPINE, DHTTYPE);
int foco=0, bomba=0, led=0, srventanas=0, srvpuertas=0;//Se declaran variables globales.
float humedad, temperatura, senter;   
void setup() {  //Se inicializan las salidas fisicas (pines), de cada componente en el arduino, usando las constantes antes definidas.  
  pinMode(FOCO, OUTPUT); 
  pinMode(VENTI, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(LED, OUTPUT); 
  pinMode(SRVVENTW, OUTPUT);
  pinMode(SRVPUERW, OUTPUT);
  pinMode(SRVVENTE, OUTPUT);
  pinMode(SRVPUERE, OUTPUT);
  digitalWrite(FOCO, 1);
  seventw.attach(SRVVENTW); 
   seventw.write(60);
  sepuerw.attach(SRVPUERW);
   sepuerw.write(15);
  sevente.attach(SRVVENTE); 
   sevente.write(150);
  sepuere.attach(SRVPUERE);
   sepuere.write(135);
  Serial.begin(9600);
  dhtw.begin();
  dhte.begin();
}
void regreValores(){ //Manda a el monitor serial y por lo tanto a "C" los valores obtenidos por los sensores y el estado de cada componente en tiempo real.
   Serial.print(foco);
   Serial.print(bomba);
   Serial.print(led);;
   Serial.print(srventanas);
   Serial.print(srvpuertas);
   Serial.print(temperatura);
   Serial.print(humedad);
   Serial.print(senter);  
   return;
}
void loop() {//Se lleva a cabo el sensado de datos para sensores tanto como el estado de los componentes.
    humedad = (dhtw.readHumidity()+dhte.readHumidity())/2;//Sensado de humedas;//Sensado de humedas
    temperatura = (dhtw.readTemperature()+dhte.readTemperature())/2;//Sensado de temperatura
    senter = (dhte.computeHeatIndex(temperatura, humedad, false)+dhte.computeHeatIndex(temperatura, humedad, false))/2;//Calculo de la sensacion termica
    regreValores();//Manda al arduino los valores obtenidos y el estado de los componentes.
    if(Serial.available()>0){//Recibe los datos del monitor serial, por tanto de "C", y administra a cada actuador deacuerdo a lo recibido.
       char pal;
       pal=Serial.read();
       switch (pal) {
          case 'f':
            if(foco==0)//Administra a el foco.
                digitalWrite(FOCO, 0);
            else 
                digitalWrite(FOCO, 1);
            foco++;
            foco%=2;
            break;
          case 'b':
            if(bomba==0)//Administra a las bombas de agua.
              analogWrite(BOMBA, 100);
            else
              analogWrite(BOMBA, 0);
            bomba++;
            bomba%=2;
            break;
          case 'l':
            if(led==0)//Administra a las luces LED.
              digitalWrite(LED, 1);
            else 
              digitalWrite(LED, 0);
            led++;
            led%=2;
            break;
          case 'v':
            if(srventanas==0){//Administra a el motor de la ventila.
                digitalWrite(VENTI, 1);
                seventw.write(10);
                sevente.write(80);
            }
            else {
                digitalWrite(VENTI, 0);
                seventw.write(60);
                sevente.write(150);
            }
            srventanas++;
            srventanas%=2;
            break;
          case 'p':
            if(srvpuertas==0){//Administra a el motor de la puerta.
                sepuerw.write(90);           
                sepuere.write(50);
            }
            else {
                sepuerw.write(15);
                sepuere.write(135);
            }
            srvpuertas++;
            srvpuertas%=2;
            break;
      }
    }
    delay(1000);
 }
