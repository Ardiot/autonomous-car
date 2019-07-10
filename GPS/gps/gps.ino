
#define int radio = 15;  // radio de llegada del nodo al que vas
#define int radio_ampli = 20 ; // radio cerca del nodo final dentro del cual siempre vas a ir girando para aproximarte lo maximo 
#define int angulo_tope = 7 ; //angulo a partir del cual vas a girar fuera del radio_ampli
#define int distancia_aux = 100 ; //distancia a partir de la cual ira mas rapido , o estara mas tiempo acelerando , para en las rectas poder acelerar mas 


  int grados, grado_anterior, distancia;
  float inicial_x,inicial_y,inter_x,inter_y,destino_x,destino_y ;
  boolean sentido ;
  VECTOR vector21,vector23;
  
  
  typedef struct {
    float x , y ;
  }vector
  
  
  void setup (){
    
    Serial.begin(9600);
      while (!Serial)  ;       //solo para el leonardo o er proMicro 
      Serial.print("Probando SD card...");
      pinMode(10, OUTPUT);         // Esto es necesario aunque creas que no lo usas.
      if (!SD.begin(chipSelect))
           {  
             Serial.println("No hay tarjeta");
              return;    // NO sigas
           }
      Serial.println("Sd encontrada.");
      File dataFile = SD.open("ruta.xml");
     if (dataFile)   // Si ha podido abrir el fichero
        {    
          Serial.print("Archivo abierto correctamente ");                        // Cierra el fichero al acabar
        }
     else     // SI no puede abrir el fichero
           Serial.println("Error, no puedo usar indes.htm");
    
    
    
    
    
  //diversas cosas por aqui
  angulo = 0 ;
  
  inicial_x=gps.x ; inicial.y=gps.y ;
  
  //y alguna mas tambien 
    
  }
  
  void loop (){
    
    
    do 
     {
       
      final_x= nueva_lectura_x ;//fscanf(f_in ,%f,&final_x)  creo que es un for con i<lo que mida una coordenada y meterlo en un array y pasarlo a float y asi cada vez 
      final_y = nueva_lectura_y ;//fscanf(f_in ,%f,&final_y)
    
          while( ( (gps.x< final_x + radio)  && ( gps.x >final_x - radio ) ) && ( ( gps.y<final_y+radio ) && (gps.y >final_y-radio   ) )  )
          {
            
            //nos movemos hacia delante , da igual la direccion , un pid con el valor anterior de la funcion giramos 
            
             
            if(grados > angulo_tope ||  ( ( (gps.x< final_x + radio_ampli)  && ( gps.x >final_x - radio_ampli ) ) && ( ( gps.y<final_y+radio_ampli ) && (gps.y >final_y-radio_ampli   ) )  ) )
              {
                if(grado> grado_anterior)
                {
                  sentido != sentido ;
                  giramos(sentido); // la fincionn giramos sera la encargada de girar el coche , o puedo hacer una que haga todo y que vea si hay que girar o no , podria ser asi : giramos(grados,sentido,distancia,giro(es un booleano) ) {} 
                }
                else 
                    giramos(sentido); // giramos en el sentido que lo estabamos haciendo , porque lo estabamos haciendo bien 
                    //avanzamos rectos 
              }
              
             else 
               {
             //no giramos , 
             // solo aceleramos 
               }
             
             
            
            grado_anterior = grado ; // cada vez vamos guardando el grado anterior para ver si cambiamos el sentido 
            
            inter_x=gps.x ; 
            inter_y=gps.y ;
            
            vector21.x= inicial_x -inter_x;
            vector21.y= inicial_y - inter_y;
            
            vector23.x= final_x -inter_x;
            vector23.y= final_y - inter_y;
            
            distancia= abs( sqrt( ( final_x - inter_x )**2  + ( final_y - inter_y)**2  ) ) ;
            
            
            inicial_x=gps.x ; 
            inicial_y=gps.y ;
            
            
            grados=giramos(180 - ang_vector(vector21,vector23);//claro , aqui hay que ver si giramos ya o lo dejamos para l¡el principio dejandole un valor de angulo y que lo meta en su PID
            //es decir , si hacemos que giramos sea una funcion que gire el coche ella misma o que nos duevulva un valor 
            
          }
    
    }while( File.Available() ) ;
    
  }
  
  int ang_vector( vector vector1 , vector vector2 ){
    
    //cos alpha = |produc escalar | / (modulo1*modulo2 )
    
    int producto_escalar = vector1.x*vector2.x + vector1.y*vector2.y ;
    int modulo1= sqrt(vector1.x**2 + vector1.y**2);
    int modulo2= sqrt(vector2.x**2 + vector2.y**2);
    
    return ( 1/cos( abs(producto_escalar)/(modulo1*modulo2) )  ) ;
    
    
    
    
  }
  
  

