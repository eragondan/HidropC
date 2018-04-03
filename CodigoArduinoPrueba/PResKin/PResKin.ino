int foco=0, bomba=1, led=0, srventanas=1, srvpuertas=1;//Se declaran variables globales.
float humedad=33.33, temperatura=55.55, senter=66.66;  
void setup() {
  Serial.begin(9600);
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
   //0000022.5027.5021.52
   //0101155.5533.3366.66
   return;
}
void loop() {
  regreValores();
  delay(1000);
}
