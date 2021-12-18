bool som;
int qt = 0;
int momentoPalma = 0;
int intervaloPalmas = 500;  //Valor representa um tempo em milissegundos, é o intervalo máximo permitido entre uma sequência de palmas.  
long esperaPalma= 0; 

#define pinSom 2

#define rele1 6
#define rele2 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinSom, INPUT);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  som = digitalRead(pinSom);

  if(!som){ 

      if(momentoPalma == 0){
        Serial.println("PRESENÇA DE SOM");
        momentoPalma = esperaPalma = millis();
        qt++;
      }else if((millis() - esperaPalma) >= 200){ //Se o intervalo da palma for maior que 200 segundo, significa que o proximo som será outra palma, não a mesma.
        momentoPalma = 0;
      }
  }//EndIf


   if(((millis() - esperaPalma) > intervaloPalmas) && (qt !=0)){  
      if(qt == 2) { digitalWrite(rele1, !digitalRead(rele1)); Serial.println("RELE 1 Acionado");}
      if(qt == 3) { digitalWrite(rele2, !digitalRead(rele2)); Serial.println("RELE 2 Acionado");}
   qt = 0; 
     
   }//Endif

}//endLoop
