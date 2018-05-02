#include "estructuras.c"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define COLORFONDO 9
#define COLORCONTRASTE 10

void limpiaConsolin(){
    int x; 
    gotoxy(34,18);
    for(x=1;x<=26;x++)
            putchar(176);
    textbackground(COLORFONDO);
}
void imprimeConsolin(char *frase){ //Recibe cadena y lo imprime en lugar especifico x=34 y=8
    textbackground(0);
    gotoxy(34,18);
    printf("%s", frase);
    getch();
    limpiaConsolin();
    return;      
}
void imprimeConsolinDelay(char *frase, int d){
    textbackground(0);
    gotoxy(34,18);
    printf("%s", frase);
    Sleep(d);
    limpiaConsolin();
    return;      
}
void imprimeConsolinF(float val, char *par){ //Consolin que recibe floats
    textbackground(0);
    gotoxy(34,18);
    printf("%s",par);
    gotoxy(39,18);
    printf("%2.2f", val);
    getch();
    limpiaConsolin();
    return;      
}
void imprimeConsolinI(int val, char *par){ //Consolin que recibe ints 
    textbackground(0);
    gotoxy(34,18);
    printf("%s",par);
    gotoxy(39,18);
    printf("%i", val);
    getch();
    limpiaConsolin();
    return;      
}
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
      archivoImagen=fopen("recursos//fondos.hid", "rb");
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
void leerTiempo(int *algo){ //Recibe strings par mostrarlo en x=34 y=8 y convierte en int para guardar
     char lec[6];
     int p;
     gotoxy(34,18);
     scanf("%s",lec);
     imprimeConsolin(lec);
     *algo=tiempoStrToInt(lec);
     return;
}
void recibeString(char *algo){ //Recibe string para guardar en struct
     gotoxy(34,18);
     scanf("%s",algo);
     return;
}
void recibeInt(int *algo){ //Recibe int para guardar en struct
     gotoxy(34,18);
     scanf("%i",algo);
     return;
}
void recibeFloat(float *algo){ //Recibe float para guardar en struct
     float tempF;
     gotoxy(34,18);
     scanf("%f",&tempF);
     *algo=tempF;
     return;
}
