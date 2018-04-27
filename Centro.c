#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include "rs232.c"
#define COLORFONDO 9
#define COLORCONTRASTE 10

int cport_nr=4  ,        //Puerto donde se coloca el arduino menos uno COM1=0
  bdrate=9600;       //Tiempo sincrono con arduino, Estandar: 9600
//--------------------------------------------------------ESTRUCTURAS---------------------------------------------------------- 
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
typedef struct moldeConfig configuracion; //Estructura de configuracion

configuracion configuracionActual;

struct moldePixel{
       int background;
       int color;
       char caracter;
};
struct moldeImagen{
       struct moldePixel pixel[20][60];
};
typedef struct moldeImagen imagen;  //Molde de la estructura de imagen

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
typedef struct moldeDatos datos;//Estructura de datos

datos dataActual; 
//--------------------------------------------------------FUNCIONES DE TIEMPO-------------------------------------------------------
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
//---------------------------------------------------FUNCIONES GENERALES DE INTERFAZ------------------------------------------------
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
//-----------------------------------------------------COMUNICACION CON ARDUINO-----------------------------------------------------
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
//---------------------------------------------------FUNCIONES DE REGISTROS-----------------------------------------------
void printRegistros(){
   char tiempoLocoAmen[6];
   tiempoIntToStr(dataActual.tiempo,tiempoLocoAmen);
   gotoxy(29,4);
   printf(dataActual.nomCultivo); //Nombre del Cultivo
   gotoxy(27,3);
   printf(dataActual.fecha); // Fecha 
   gotoxy(39,3);
   printf("%s", tiempoLocoAmen);
   gotoxy(46,6);
   printf("%.2f",dataActual.temperatura); //Temperatura 
   gotoxy(46,8);
   printf("%.2f",dataActual.humedad); //Nivel de Humedad
   gotoxy(46,10);
   printf("%.2f",dataActual.senterm); // SensaciÃ³n Termica
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
void modificaDataBin(){
      FILE *archivoData;
      archivoData=fopen("..//data.dts", "ab");
      fseek(archivoData,1*sizeof(datos),SEEK_END);
      fwrite(&dataActual,sizeof(datos),1,archivoData);
      fclose(archivoData);
      imprimeConsolin("Archivo Guardado");
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
                   modificaPrincipal();
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
//---------------------------------------------------FUNCIONES DE CONFIGURACIONES-----------------------------------------
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
void modificaConfigBin(){
      FILE *archivoConfig;
      archivoConfig=fopen("config.cfg", "wb");
      fseek(archivoConfig,0*sizeof(configuracion),SEEK_SET);
      fwrite(&configuracionActual,sizeof(configuracion),1,archivoConfig);
      fclose(archivoConfig);
      imprimeConsolin("Archivo Guardado");
}
void leeConfigBin(){
      FILE *archivoConfig;
      archivoConfig=fopen("config.cfg", "rb");
      fseek(archivoConfig,0*sizeof(configuracion),SEEK_SET);
      fread(&configuracionActual,sizeof(configuracion),1,archivoConfig);
      fclose(archivoConfig);
}
void modificaConfig(){
    char opciones(int *x){
         switch(*x){
             case 6: // Nombre del cultivo
                  imprimeConsolin("Int Nombre Cultivo");
                  recibeString(configuracionActual.nomCultivo);
                  imprimeConsolin(configuracionActual.nomCultivo);
             break;
             case 8: //Temperatura max y min
                  imprimeConsolin("Ingresa Maximo");
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
                  printImagenFondo(2);
                   modificaPrincipal();
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
//--------------------------------------------------------INTERFACES--------------------------------------------------------
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
//----------------------------------------FUNCIONES DE INTERFAZ PRINCIPAL--------------------------------------------------------
void printDatos(){
   char tiempoTemp[6];
   tiempoIntToStr(dataActual.tiempo,tiempoTemp);
   gotoxy(14,3);
   printf(dataActual.nomCultivo); //Nombre del Cultivo
   gotoxy(39,2);
   printf("%s",dataActual.fecha); // Fecha 
   gotoxy(50,2);
   printf("%s",tiempoTemp);
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
   else
     printf("OFF");
   gotoxy(32,12);
   if(dataActual.bomba!=0) //Bomba
     printf("ON ");
   else
     printf("OFF");
   gotoxy(32,13);
   if(dataActual.ventanas!=0) //Ventana
     printf("ON ");
   else
     printf("OFF");
   gotoxy(32,14);
   if(dataActual.foco!=0) //Foco
     printf("ON ");
   else
     printf("OFF");
   gotoxy(41,11); // Tiempo Inicio de Iluminacion
   tiempoIntToStr(configuracionActual.confIlumiIni,tiempoTemp);
   printf("%s",tiempoTemp);
   gotoxy(41,12); // Tiempo Inicio de Riego
   tiempoIntToStr(configuracionActual.confRiegoIni,tiempoTemp);
   printf("%s",tiempoTemp);
   gotoxy(51,11);
   printf("%i",configuracionActual.confIlumiDur); // Duración de la Ilumninacion
   gotoxy(51,12);
   printf("%i",configuracionActual.confRiegoDur); //Duracióo del Riego
        
   return;
}
void modificaPrincipal(){
    char opciones(int *x){
         switch(*x){
             case 11: // Iluminacion
                RS232_cputs(cport_nr,"l");
             break;
             case 12: //Riego
                RS232_cputs(cport_nr,"b");
             break;
             case 13: //Ventilación
                RS232_cputs(cport_nr,"v");
             break;
             case 14: //Calentador
                RS232_cputs(cport_nr,"f"); 
             break;
             case 16: // Guardar
                  modificaDataBin();
             break;
             case 17: //Revisar
                  printImagenFondo(3);
                  leeDataBin(0);
                  printRegistros();
                  modificaRevision();
             break;
             case 18: //Editar
                  printImagenFondo(4);
                  modificaConfig();
             break;
             case 19: //Salir
                 printImagenFondo(1);
                 getch();
                 exit(1);
             break;
         }
        return;
    }
    char opcion;
    int x=6, y=11;
    while(opcion!='x'){
       getData();
       ponFecha();
       tiempoCompu();
       strcpy(dataActual.nomCultivo,configuracionActual.nomCultivo);
       printDatos();
       /*if(!feof(stdin)){
          opcion=getch();              
       }*/
       /*fseek (stdin, 0, SEEK_END);
       int num = ftell (stdin);
       printf("%i", num);*/
       if(kbhit())
                 opcion=getch();
       Sleep(200);
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
       opcion='0';
       gotoxy(x, y);
       putchar(62);
    };
    return;
}
//El buffer maximo es de 60 en X y 20 en Y
//El buffer minimo es de 1 en X y 1 en Y*/
//--------------------------------------------------MAIN---------------------------------------------------
int main(){
    _setcursortype(NULL);
    prepVentana();
    checkPort();
    printImagenFondo(1);
    getch();
    printImagenFondo(2);
    /*strcpy(dataActual.nomCultivo,"AJO"); 
    strcpy(dataActual.fecha,"21/07/21");
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
    modificaPrincipal();
    return 0;
}

    /*   prepVentana();
   printImagenFondo(2);
   printDatos();
   modificaPrincipal();
   getch();*/
    //return 0;

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
    //Pedir datos
    /*while(1){

    Sleep(1000);
    } */
