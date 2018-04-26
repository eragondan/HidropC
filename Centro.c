#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include "rs232.c"
#define COLORFONDO 9
#define COLORCONTRASTE 10

int cport_nr=5  ,        //Puerto donde se coloca el arduino menos uno COM1=0
  bdrate=9600;       //Tiempo sincrono con arduino, Estandar: 9600

struct moldePixel{
       int background;
       int color;
       char caracter;
};
struct moldeImagen{
       struct moldePixel pixel[20][60];
};
typedef struct moldeImagen imagen;  
struct moldeDatos{
       char nomCultivo[15];
       char fecha[9];
       float temperatura;
       float humedad;
       float senterm;  
       int tiempo;
       int leds;
       int bomba;
       int ventanas;
       int foco;
       int puertas;
};
typedef struct moldeDatos datos;

datos dataActual;    

//--------------------------------------------------------COMUNICACION----------------------------------------------------------  
void getData(){//Obtienen los datos del arduino y los almacena dentro de una estructura.
   unsigned char buf[4096], buf2[4096]; 
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
    printf("foco: %i bomba: %i leds: %i ventanas: %i puertas: %i temp: %0.2f humedad: %0.2f senterm: %0.2f\n", dataActual.foco, dataActual.bomba, dataActual.leds, dataActual.ventanas, dataActual.puertas, dataActual.temperatura, dataActual.humedad, dataActual.senterm);
    printf("%s\n",mane);  
}
int checkPort(){//Checa el puerto
    char mode[]={'8','N','1',0};
    textcolor(12);   
    if(RS232_OpenComport(cport_nr, bdrate, mode)){
        getchar();
        return 1;
        }
}
//--------------------------------------------------------TIEMPO---------------------------------------------------------

void ponFecha(){//Esta funcion fija dentro de la estructura dataActual la fecha como cadena.
     time_t tiempo = time(0);
     struct tm *tlocal = localtime(&tiempo);
     char fech[9];
     strftime(fech,9,"%d/%m/%y",tlocal);
     strcpy(dataActual.fecha,fech);
     }
int tiempoStrToInt(char *tiempo){//Recibe un String y regresa en el integer el numero de minutos pasados en el dia.
     int min=1, mtemp;;
     char hr[3], mn[3];
     hr[0]=tiempo[0];
     hr[1]=tiempo[1];
     hr[2]='\0';
     mn[0]=tiempo[3];
     mn[1]=tiempo[4];
     mn[2]='\0';
     min=atoi(hr);
     mtemp=atoi(mn);
     min=min*60+mtemp;
     return min;
     }
void tiempoCompu(){//Esta funcion devuelve el tiempo de computadora en minutos transcurridos del dia.
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    int horaReal;
    char hors[3], mins[3];
    strftime(hors,6,"%H:%M",tlocal);
    horaReal=tiempoStrToInt(hors);
    dataActual.tiempo=horaReal;
    return;
}
void tiempoIntToStr(int min, char *tiempo){//Recibe un integer y regresa en la cadena tiempo la hora deacuerdo a los minutos transcurridos.
     int horas, minres;
     char hor[3],mn[3];
     horas = min / 60;
     minres = min % 60;
     itoa(minres,mn,10); 
     itoa(horas,hor,10);
     strcpy(tiempo, hor);
     strcat(tiempo, ":");
     strcat(tiempo, mn);
     return;   
}
//--------------------------------------------------------CONFIGURACIONES-------------------------------------------------


//--------------------------------------------------------INTERFAZ--------------------------------------------------------
void prepVentana(){
     SetConsoleTitle("SISTEMA HIDROPONICO");
     system("mode con: cols=61 lines=20");
}
int printImagenFondo(int numeroFondo){
      numeroFondo-=1;
      int x, y;
      char letra;                  
      imagen imagenFondo;
      FILE *archivoImagen;
      archivoImagen=fopen("fondos.hid", "rb");
      fseek(archivoImagen,numeroFondo*sizeof(imagen),SEEK_SET);
      fread(&imagenFondo,sizeof(imagen),1,archivoImagen);
      for(y=0;y<20;y++)
      for(x=0;x<60;x++){
               letra=imagenFondo.pixel[y][x].caracter;
               textcolor(imagenFondo.pixel[y][x].color);
               textbackground(imagenFondo.pixel[y][x].background);
               gotoxy(x+1,y+1);
               putchar(letra);
      }
      textcolor(COLORCONTRASTE);
      textbackground(COLORFONDO);
      fclose(archivoImagen);
      return 0;
}
void imprimeConsolin(char *frase){
    int x;
    textbackground(0);
    gotoxy(34,18);
    printf("%s", frase);
    getch();
    gotoxy(34,18);
    for(x=1;x<=25;x++)
            putchar(176);
    textbackground(COLORFONDO);
    return;      
}
//El buffer maximo es de 60 en X y 20 en Y
//El buffer minimo es de 1 en X y 1 en Y*/
//--------------------------------------------------MAIN---------------------------------------------------
int main(){
    char tiempo[6];
    prepVentana();
    //checkPort();
    printImagenFondo(1);
    getch();
    printImagenFondo(2);
    getch();
    /*while(1){
    getData();
    Sleep(1000);
    } */
    getch();
    return 0;
}
//Ejemplos de uso de funciones
    /*imprimeConsolin("MAXIMO DE ESTE CUADRO 25");
    printf("\n%i",tiempoStrToInt("15:23"));
    tiempoAMin();
    printf("%i\n", dataActual.tiempo);
    tiempoIntToStr(dataActual.tiempo,tiempo);
    puts(tiempo);
    ponFecha();
    printf("%s",dataActual.fecha);
    tiempoCompu();
    printf("%i",dataActual.tiempo);*/
