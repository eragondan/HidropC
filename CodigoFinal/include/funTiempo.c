#include <time.h>
#include "funTiempo.h"
void ponFecha(char *direccion){//Esta funcion fija dentro de la estructura dataActual la fecha como cadena.
     time_t tiempo = time(0);
     struct tm *tlocal = localtime(&tiempo);
     char fech[9];
     strftime(fech,9,"%d/%m/%y",tlocal);
     strcpy(direccion,fech);
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
void tiempoCompu(int *direccion){//Esta funcion devuelve el tiempo de computadora en minutos transcurridos del dia.
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    int horaReal;
    char hors[3], mins[3];
    strftime(hors,6,"%H:%M",tlocal);
    horaReal=tiempoStrToInt(hors);
    *direccion=horaReal;
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
