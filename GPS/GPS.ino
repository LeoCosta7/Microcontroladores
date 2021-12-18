#include <Arduino.h>

#include <SoftwareSerial.h>      
#include <TinyGPS.h>          

int TX = 10;
int RX = 11;

TinyGPS gps1;
SoftwareSerial SerialGPS(TX, RX);

void setup() {

    SerialGPS.begin(9600);
    Serial.begin(9600);


} //END_SETUP ---

void loop() {

    bool recebido = false;

    while(SerialGPS.available()){           //Verifica se há alguma informação disponível
        char a = SerialGPS.read();          //Lendo a informação
        recebido = gps1.encode(a);          //Cada byte de dados NEMA deve ser fornecido ao TinyGPS usando encode ().
    }

    long latitude, longitude;
    unsigned long idadeInfo;
    
    gps1.get_position(&latitude, &longitude, &idadeInfo);           
    
    if(latitude != TinyGPS::GPS_INVALID_F_ANGLE){                   //Verifica se a informação recebida é válida
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 1000, 6);
    }

    if(longitude != TinyGPS::GPS_INVALID_F_ANGLE){                  
        Serial.print("Logitude: ");
        Serial.println(float(longitude) / 1000, 6);
    }
    if(idadeInfo != TinyGPS::GPS_INVALID_AGE){                    
        Serial.print("Idade da informacao (ms): ");
        Serial.println(idadeInfo);
    }


    //======= Dia e Hora =======

    int ano;
    byte mes, dia, hora, minuto, segundo, centesimo;
    
    gps1.crack_datetime(&ano ,&mes ,&dia ,&hora ,&minuto ,&segundo ,&centesimo);

    Serial.print("Data (GMT): ");
    Serial.print(dia);
    Serial.print("/");
    Serial.print("mes");
    Serial.print("/");
    Serial.print(ano);

    Serial.print("Horario (GMT): ");
    Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.print(":");
    Serial.print(centesimo);


    
    //======= Altitude =======

    float altitudeGPS;
    altitudeGPS = gps1.f_altitude();

    if((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE)){
        Serial.print("Altitude (cm): ");
        Serial.print(altitudeGPS);
    }


    //======= Velocidade =======

    float velocidade; 
    velocidade = gps1.f_speed_kmph();
    
    Serial.print("Velocidade (km/h): ");
    Serial.print(velocidade, 2);


    //=======  Satelites e precisão ======= 

    unsigned short satelites;
    unsigned long precisao;

    satelites = gps1.satellites();
    precisao = gps1.hdop();

    if(satelites != TinyGPS::GPS_INVALID_SATELLITES){
        Serial.print("Satelites: ");
        Serial.print(satelites);
    }

    if(precisao != TinyGPS::GPS_INVALID_HDOP){
        Serial.print("Precisao: (centesimos de segundos) ");
        Serial.print(precisao);
    }



/*
    // ======= DISTANCIA E SENTIDO =======
    float distancia_entre;
    distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);       //Distancia entre esses dois pontos;

    float sentido;
    sentido = gps.couse_to(lat1, long1, lat2, long2);                       //Sentido de deslocamento do ponto 1 para o ponto 2.

*/

} //END_LOOP ---
