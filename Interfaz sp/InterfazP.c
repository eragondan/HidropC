#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#define COLORFONDO 9
#define COLORCONTRASTE 10
 
struct moldeDatos{
       char nomCultivo[15];
       char fecha[9];
       float temperatura;//5
       float humedad;//5
       float senterm;//5  
       int tiempo;//5
       int leds;//1
       int bomba;//1
       int ventanas;//1
       int foco;//1
       int puertas;//1
};
typedef struct moldeDatos datos;

datos dataActual; 

struct moldeConfig{
       char nomCultivo[15];
       float confMaxTemperatura;
       float confMinTemperatura;
       float confMaxHumedad;
       float confMinHumedad; 
       int confIlumiIni;
       int confIlumiDur;
       int confRiegoIni;
       int confRiegoDur; 
};
typedef struct moldeConfig configuracion;

configuracion configuracionActual;

struct moldePixel{
       int background;
       int color;
       char caracter;
};
struct moldeImagen{
       struct moldePixel pixel[20][60];
};
typedef struct moldeImagen imagen;  
//---------------------------------------------
void modificaPrincipal(){
    char opciones(int *x){
         switch(*x){
             case 11: // Iluminacion
                
             break;
             case 12: //Riego
                
             break;
             case 13: //Ventilación
                
             break;
             case 14: //Calentador
                 
             break;
             case 16: // Guardar
                  
             break;
             case 17: //Revisar
                 
             break;
             case 18: //Editar
                
             break;
             case 19: //Salir
                 
             break;
         }
        return;
    }
    char opcion;
    int x=6, y=11;
    while(opcion!='x'){
       opcion=getch();
       gotoxy(x, y);
       putchar('\0');
       switch (opcion){
       
           case 'w'://arriba
                if(y>11){
                        y-=1;
                        if(y==15)
                         y=14;}
           break;
           case 's'://abajo
                if(y<=18){
                        y+=1; 
                        if(y==15)
                         y=16;}
           break;  
           case 'd'://introducir
               opcion=opciones(&y);
           break;   
       }
       gotoxy(x, y);
       putchar(62);
    };
    return;
}
//-------------------------------------Interfaz-----------------------------------------------------
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
      archivoImagen=fopen("../fondos.hid", "rb");
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
//---------------------------------Datos-----------------------------------------------------------

void printDatos(){
   gotoxy(14,3);
     printf(dataActual.nomCultivo); //Nombre del Cultivo
   gotoxy(39,2);
     printf(dataActual.fecha); // Fecha 
   gotoxy(50,2);
     printf("30:70");
   gotoxy(32,5);
     printf("%.2f",dataActual.temperatura); //Temperatura 
   gotoxy(41,5);
     printf("%.2f",configuracionActual.confMaxTemperatura); //Maximo de la Temperatura
   gotoxy(50,5);
     printf("%.2f",configuracionActual.confMinTemperatura); //Minimo de la Temperatura
   gotoxy(32,6);
     printf("%.2f",dataActual.humedad); //Nivel de Humedad
   gotoxy(41,6);
     printf("%.2f",configuracionActual.confMaxHumedad); //Maximo de Humedad
   gotoxy(50,6);
     printf("%.2f",configuracionActual.confMinHumedad); //Minimo de Humedad
   gotoxy(32,7);
     printf("%.2f",dataActual.senterm); // Sensación Termica
   gotoxy(32,11);
     if(dataActual.leds!=0)  //Luces Led
         printf("ON ");
   gotoxy(32,12);
     if(dataActual.bomba!=0) //Bomba
         printf("ON ");
   gotoxy(32,13);
     if(dataActual.ventanas!=0) //Ventana
         printf("ON ");
   gotoxy(32,14);
     if(dataActual.foco!=0) //Foco
         printf("ON ");
   gotoxy(41,11); // Tiempo Inicio de Iluminacion
     printf("20:30");
   gotoxy(41,12); // Tiempo Inicio de Riego
     printf("30:20");
   gotoxy(51,11);
     printf("%i",configuracionActual.confIlumiDur); // Duración de la Ilumninacion
   gotoxy(51,12);
    printf("%i",configuracionActual.confRiegoDur); //Duracióo del Riego
        
   return 0;
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   /*strcpy(dataActual.nomCultivo,"AJO"); 
   strcpy(dataActual.fecha,"20/20/00");
   dataActual.temperatura=12.21;
   configuracionActual.confMaxTemperatura=23.32;
   configuracionActual.confMinTemperatura=32.23;
   dataActual.humedad=21.12;
   configuracionActual.confMaxHumedad=34.43;
   configuracionActual.confMinHumedad=43.34;
   dataActual.senterm=78.89;
   dataActual.leds=0;
   dataActual.bomba=0;
   dataActual.ventanas=0;
   dataActual.foco=0;
   configuracionActual.confIlumiDur=2;
   configuracionActual.confRiegoDur=3;*/
   
   prepVentana();
   printImagenFondo(2);
   printDatos();
   modificaPrincipal();
   getch();
   return 0;
}