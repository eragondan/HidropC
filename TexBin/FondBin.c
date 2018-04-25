 #include <stdio.h>
 #include <stdlib.h>
 #include <conio.h>
 
 #define COLORFONDO 9
 #define COLORCONTRASTE 10
 
 struct moldePixel{
        int background;
        int color;
        char caracter;
 };
 struct moldeImagen{
        struct moldePixel pixel[20][60];
 };
 typedef struct moldeImagen imagen;
 
 imagen imagenActual;
 void textoBinario(char *dir, int numeroFondo){
      numeroFondo-=1;
      int x=0, y=0;
      char letra;
      FILE *texto;
      texto=fopen(dir, "r");
      while(!feof(texto)&&y<20){
            letra=fgetc(texto);
            if(letra!=10){
                   if(x<=60){
                      imagenActual.pixel[y][x].caracter=letra;
                      switch (letra){
                      case '1'://Marco o Gruesas
                            imagenActual.pixel[y][x].background=COLORCONTRASTE;
                            imagenActual.pixel[y][x].color=COLORCONTRASTE;
                      break;
                      case '2'://ColoresContrastados en negro
                            imagenActual.pixel[y][x].background=0;
                            imagenActual.pixel[y][x].color=COLORCONTRASTE;
                            imagenActual.pixel[y][x].caracter=176;
                      break;
                      default://Texto comun
                           imagenActual.pixel[y][x].background=COLORFONDO;
                           imagenActual.pixel[y][x].color=COLORCONTRASTE;
                      break;
                      }
                      x++;
                      if(x==60){
                         x=0;
                         y++;
                      }
                   }
                   
            }
      }
      fclose(texto);
      printf(dir);
      FILE *archivoImagen;
      archivoImagen=fopen("..//fondos.hid", "rb+");
      fseek(archivoImagen,numeroFondo*sizeof(imagen),SEEK_SET);
      fwrite(&imagenActual,sizeof(imagen),1,archivoImagen);
      fclose(archivoImagen);
      printf(" Archivo Guardado\n");
      getch();
      return;
 }
  
 
 int printImagenFondo(int numeroFondo){
      numeroFondo-=1;
      int x, y;
      char letra;                  
      imagen imagenFondo;
      FILE *archivoImagen;
      archivoImagen=fopen("..//fondos.hid", "rb");
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
 void checaTodos(){
      textoBinario("Titulo.txt",1);
      textoBinario("InterfazPrincipal.txt",2);
      textoBinario("Registros.txt",3);
      textoBinario("Edicion.txt",4);
      return;
 }

 int main(){
     int t;
     char direccion[50]="Registros.txt";
     system("mode con: cols=61 lines=20");
     checaTodos();
     while(1)
     for(t=1;t<=4;t++){
     printImagenFondo(t);
     getch();
     }
     return 0;
     }
