#include <stdio.h>
#include <windows.h>
#include <conio.h>
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

/*struct moldeConfig{
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
typedef struct moldeConfig configuracion;*/

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
                  printf("%i",*x);
             break;
             case 12: //Riego
                  printf("%i",*x);
             break;
             case 13: //Ventilación
                  printf("%i",*x);
             break;
             case 14: //Calentador
                  printf("%i",*x);
             break;
             case 16: // Guardar
                  printf("%i",*x);
             break;
             case 17: //Revisar
                  printf("%i",*x);
             break;
             case 18: //Editar
                  printf("%i",*x);
             break;
             case 19: //Salir
                  printf("%i",*x);
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
                if(y>11)
                        y-=1;
           break;
           case 's'://abajo
                if(y<=18)
                        y+=1; 
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
//-----------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   prepVentana();
   printImagenFondo(2);
   modificaPrincipal();
   getch();
   return 0;
}