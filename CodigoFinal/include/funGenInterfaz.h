#ifndef funGenInterfaz_h 
#define funGenInterfaz_h 
void limpiaConsolin();
void imprimeConsolin(char *frase);
void imprimeConsolinDelay(char *frase, int d);
void imprimeConsolinF(float val, char *par);
void imprimeConsolinI(int val, char *par);
void prepVentana();
int printImagenFondo(int numeroFondo);
void leerTiempo(int *algo);
void recibeString(char *algo);
void recibeInt(int *algo);
void recibeFloat(float *algo);
#endif