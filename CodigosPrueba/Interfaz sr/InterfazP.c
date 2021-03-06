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

struct moldePixel{
       int background;
       int color;
       char caracter;
};
struct moldeImagen{
       struct moldePixel pixel[20][60];
};
typedef struct moldeImagen imagen;  

//------------------------------Datos----------------------------------------------
void printRegistros(){
   gotoxy(29,4);
   printf(dataActual.nomCultivo); //Nombre del Cultivo
   gotoxy(27,3);
   printf(dataActual.fecha); // Fecha 
   gotoxy(39,3);
   printf("30:70");
   gotoxy(46,6);
   printf("%.2f",dataActual.temperatura); //Temperatura 
   gotoxy(46,8);
   printf("%.2f",dataActual.humedad); //Nivel de Humedad
   gotoxy(46,10);
   printf("%.2f",dataActual.senterm); // Sensación Termica
   gotoxy(46,12);
   if(dataActual.leds!=0)  //Luces Led
      printf("ON ");
   else
       printf("OFF");
   gotoxy(46,14);
   if(dataActual.bomba!=0) //Bomba
      printf("ON ");
   else
       printf("OFF");
   gotoxy(46,16);
   if(dataActual.ventanas!=0) //Ventana
      printf("ON ");
   else
       printf("OFF");
   gotoxy(46,18);
   if(dataActual.foco!=0) //Foco
      printf("ON ");
   else
       printf("OFF");
   return;
}
        
//<-----------------------------------------------------BINARIOS---------------------------------------------------->
void modificaDataBin(){
      FILE *archivoData;
      archivoData=fopen("..//data.dts", "wb");
      fseek(archivoData,1*sizeof(datos),SEEK_END);
      fwrite(&dataActual,sizeof(datos),1,archivoData);
      fclose(archivoData);
      //imprimeConsolin("Archivo Guardado");
}
void leeDataBin(int pos){ //lectura de doc binario datos
      FILE *archivoData;
      archivoData=fopen("..//data.dts", "rb");
      fseek(archivoData,pos*sizeof(datos),SEEK_SET);
      fread(&dataActual,sizeof(datos),1,archivoData);
      fclose(archivoData);
}

void modificaRevision(){
    int m=0;
    char opciones(int *x){
         switch(*x){
             case 12: // Registrar siguiente
                  m++;
                  leeDataBin(m);
                  printRegistros();
             break;
             case 14: // Registro anterios
                       if(m!=0){
                         m--;
                         leeDataBin(m);
                         printRegistros();
                       }
             break;
             case 16: //Regresar
                  printImagenFondo(2);
                  return 'x';
             break;
         }
        return;
    }
    char opcion;
    int x=3, y=12;
    while(opcion!='x'){
       opcion=getch();
       gotoxy(x, y);
       putchar('\0');
       switch (opcion){
           case 'w'://arriba
                if(y>12)
                        y-=2;
           break;
           case 's'://abajo
                if(y<16)
                        y+=2; 
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
//--------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   leeDataBin(0);
   prepVentana();
   printImagenFondo(3);
   printRegistros();
   modificaRevision();
   getch();
   return 0;
}
