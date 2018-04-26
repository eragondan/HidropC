#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define COLORFONDO 9
#define COLORCONTRASTE 10
 
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
//-----------------------------------------------------  
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
void imprimeConsolin(char *frase){ //Recibe cadena y lo imprime en lugar especifico x=34 y=8
    int x;
    textbackground(0);
    gotoxy(34,18);
    printf("%s", frase);
    getch();
    gotoxy(34,18);
    for(x=1;x<=26;x++)
            putchar(176);
    textbackground(COLORFONDO);
    return;      
}
void imprimeConsolinF(float val, char *par){ //Consolin que recibe floats
    int x;
    textbackground(0);
    gotoxy(34,18);
    printf("%s",par);
    gotoxy(39,18);
    printf("%2.2f", val);
    getch();
    gotoxy(34,18);
    for(x=1;x<=26;x++)
            putchar(176);
    textbackground(COLORFONDO);
    return;      
}
void imprimeConsolinI(int val, char *par){ //Consolin que recibe ints 
    int x;
    textbackground(0);
    gotoxy(34,18);
    printf("%s",par);
    gotoxy(39,18);
    printf("%i", val);
    getch();
    gotoxy(34,18);
    for(x=1;x<=26;x++)
            putchar(176);
    textbackground(COLORFONDO);
    return;      
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
//--------------------------------------------------------
void imprimeValoresConfiguracion(){
     int x=31, y=6;
     char iluminTem[6], riegoTem[6];
     tiempoIntToStr(configuracionActual.confIlumiIni, iluminTem);
     tiempoIntToStr(configuracionActual.confRiegoIni, riegoTem);
     gotoxy(x,y);
     printf("%s\n",configuracionActual.nomCultivo);
     gotoxy(x,y+2);
     printf("%2.2f\n",configuracionActual.confMaxTemperatura);
     gotoxy(x+10,y+2);
     printf("%2.2f\n",configuracionActual.confMinTemperatura);
     gotoxy(x,y+4);
     printf("%2.2f\n",configuracionActual.confMaxHumedad);
     gotoxy(x+10,y+4);
     printf("%2.2f\n",configuracionActual.confMinHumedad); 
     gotoxy(x,y+6);
     printf("%s\n",iluminTem);//SePasaFuncion
     gotoxy(x+10,y+6);
     printf("%i\n",configuracionActual.confIlumiDur);
     gotoxy(x,y+8);
     printf("%s\n",riegoTem);//SePasaFuncion
     gotoxy(x+10,y+8);
     printf("%i\n",configuracionActual.confRiegoDur);
     gotoxy(x,y);
   return;
     }
//--------------------------------------------------------------------------------------------------
void modificaConfigBin(){
      FILE *archivoConfig;
      archivoConfig=fopen("..//config.cfg", "wb");
      fseek(archivoConfig,0*sizeof(configuracion),SEEK_SET);
      fwrite(&configuracionActual,sizeof(configuracion),1,archivoConfig);
      fclose(archivoConfig);
      imprimeConsolin("Archivo Guardado");
}
void leeConfigBin(){
      FILE *archivoConfig;
      archivoConfig=fopen("..//config.cfg", "rb");
      fseek(archivoConfig,0*sizeof(configuracion),SEEK_SET);
      fread(&configuracionActual,sizeof(configuracion),1,archivoConfig);
      fclose(archivoConfig);
     }
//---------------------------------------------
void modificaConfig(){
    char opciones(int *x){
         switch(*x){
             case 6: // Nombre del cultivo
                  imprimeConsolin("Int Nombre Cultivo");
                  recibeString(configuracionActual.nomCultivo);
                  imprimeConsolin(configuracionActual.nomCultivo);
             break;
             case 8: //Temperatura max y min
                  imprimeConsolin("Ingrsa Maximo");
                  recibeFloat(&configuracionActual.confMaxTemperatura);
                  imprimeConsolinF(configuracionActual.confMaxTemperatura, "MAX");
                  imprimeConsolin("Presiona Enter");
                  imprimeConsolin("Ingresa Minimo");
                  recibeFloat(&configuracionActual.confMinTemperatura);
                  imprimeConsolinF(configuracionActual.confMinTemperatura, "MIN");
                  
             break;
             case 10: //Humedad max y min
                  imprimeConsolin("Ingresa Maximo");
                  recibeFloat(&configuracionActual.confMaxHumedad);
                  imprimeConsolinF(configuracionActual.confMaxHumedad, "MAX");
                  imprimeConsolin("Presiona Enter");
                  imprimeConsolin("Ingresa Minimo");
                  recibeFloat(&configuracionActual.confMinHumedad);
                  imprimeConsolinF(configuracionActual.confMinHumedad, "MIN");
             break;
             case 12: //Iluminacion
                  imprimeConsolin("Ingresa inicio(HH:MM)");
                  leerTiempo(&configuracionActual.confIlumiIni);
                 imprimeConsolin("Presiona Enter");
                  imprimeConsolin("Ingresa Duracion");
                  recibeInt(&configuracionActual.confIlumiDur);
                  imprimeConsolinI(configuracionActual.confIlumiDur, "DUR");
             break;
             case 14: //Riego
                  imprimeConsolin("Ingresa inicio(HH:MM)");
                  leerTiempo(&configuracionActual.confRiegoIni);
                  imprimeConsolin("Presiona Enter");
                  imprimeConsolin("Ingresa Duracion");
                  recibeInt(&configuracionActual.confRiegoDur);
                  imprimeConsolinI(configuracionActual.confRiegoDur, "DUR");
             break;
             case 16: //Regresar
                   return 'x';
             break;
         }
        modificaConfigBin();
        return;
    }
    char opcion;
    int x=6, y=6;
    while(opcion!='x'){
       leeConfigBin();
       imprimeValoresConfiguracion();
       opcion=getch();
       gotoxy(x, y);
       putchar('\0');
       switch (opcion){
           case 'w'://arriba
                if(y>6)
                        y-=2;
           break;
           case 's'://abajo
                if(y<=14)
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
//-----------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   prepVentana();
   printImagenFondo(4);
   /*strcpy(configuracionActual.nomCultivo,"nombrecin");
   configuracionActual.confMaxTemperatura=10.10;
   configuracionActual.confMinTemperatura=22.22;
   configuracionActual.confMaxHumedad=33.33;
   configuracionActual.confMinHumedad=44.44; 
   configuracionActual.confIlumiIni=111;
   configuracionActual.confIlumiDur=222;
   configuracionActual.confRiegoIni=333;
   configuracionActual.confRiegoDur=444; */
   modificaConfig();
   //getch();
   return 0;
}
