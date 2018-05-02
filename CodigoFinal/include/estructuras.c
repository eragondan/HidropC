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
