#include "estructuras.c"
#include <stdio.h>
#include "rs232.c"
int cport_nr=5  ,        //Puerto donde se coloca el arduino menos uno COM1=0
  bdrate=9600;       //Tiempo sincro     no con arduino, Estandar: 9600
void getData(){//Obtienen los datos del arduino y los almacena dentro de una estructura.
   unsigned char buf[4096]; 
   char mane[30], tempo[6];
   int n = RS232_PollComport(cport_nr, buf, 4095),
   h, k;
   if(n > 0)
   {
      buf[n] = 0; 
      for(h=0;h<30;h++)
          mane[h]=buf[h];
      dataActual.foco = mane[0]-'0';
      dataActual.bomba = mane[1]-'0';
      dataActual.leds = mane[2]-'0';
      dataActual.ventanas = mane[3]-'0';
      dataActual.puertas = mane[4]-'0'; 
      for(k=5;k<=15;k+=5){    
          for(h=0;h<5;h++){
              tempo[h]=mane[h+k];   
          }
          if(k==5) dataActual.temperatura=atof(tempo);
          if(k==10) dataActual.humedad=atof(tempo);
          if(k==15) dataActual.senterm=atof(tempo);
      }
   }
    //printf("foco: %i bomba: %i leds: %i ventanas: %i puertas: %i temp: %0.2f humedad: %0.2f senterm: %0.2f\n", dataActual.foco, dataActual.bomba, dataActual.leds, dataActual.ventanas, dataActual.puertas, dataActual.temperatura, dataActual.humedad, dataActual.senterm);
    //printf("%s\n",mane);  
}
int checkPort(){//Checa el puerto
    char mode[]={'8','N','1',0};
    textcolor(12);   
    if(RS232_OpenComport(cport_nr, bdrate, mode)){
        getchar();
        return 1;
        }
}