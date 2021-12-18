#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

//******* CONFIGURACAO DO PROJETO *********
#define pinRS 12
#define pinEN 13
#define pinD4 7
#define pinD5 6
#define pinD6 5
#define pinD7 4

#define linhasKB  4
#define colunasKB 4

char keys[linhasKB][colunasKB] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinLinhas[linhasKB]  = {11, 10, 9, 8}; 
byte pinColunas[colunasKB] = {A0, A1, A2, A3};


#define pinRX 3
#define pinTX 2
//*****************************************

#define estDESATIVADO 0
#define estATIVAR     1
#define estATIVADO    2
#define estDISPARADO  3
#define estCONFIRMAR  4

SoftwareSerial SerialIHM(pinRX, pinTX);
LiquidCrystal lcd(pinRS, pinEN, pinD4, pinD5, pinD6, pinD7);
Keypad keypad = Keypad( makeKeymap(keys), pinLinhas, pinColunas, linhasKB, colunasKB );

byte estado = estDESATIVADO;
byte estadoAnt = estATIVADO;

String zonas;
String senha;

void setup()
{
  SerialIHM.begin(9600);  
  lcd.begin(16, 2);
  lcd.print("   Brincando");
  lcd.setCursor(0, 1);
  lcd.print("   com Ideias");
  delay(2000);
}

void loop()
{
  if (SerialIHM.available()) {
    char recebido = SerialIHM.read();
    
    if (recebido == 'L') {
       estado = estATIVADO; 
    }
    if ((recebido >= '1') && (recebido <= '9')) {
       zonas += recebido;
       estado = estDISPARADO; 
    }
  }
  
  
  char key = keypad.getKey();
  
  if (key){
    switch (estado) { 
       case estDESATIVADO:
         if (key == 'A') {
            lcd.clear();
            lcd.print("   CONFIRMA ?");
            lcd.setCursor(0, 1);
            lcd.print(" (*)Nao  (#)Sim");
            estado = estCONFIRMAR;
         }
         break;
       case estCONFIRMAR:
         if (key == '*') {
            estado = estDESATIVADO;
         }
         if (key == '#') {
            estado = estATIVAR;
            SerialIHM.print("AAA");
         }
         break;
       case estATIVAR:
         
         break;
       case estATIVADO:
         if ((key >= '0') && (key <= '9')) {
           if (senha == "") {
              lcd.clear();
           }
           lcd.print(key);
           senha += key;
         }
      
         if (key == '#') {
           if (senha == "66555") {
              estado = estDESATIVADO; 
              lcd.clear();
              SerialIHM.print("BBB");
           } else {
              estadoAnt = 0;
           }
           senha = "";
         }

         if (key == '*') {
           estadoAnt = 0;
           senha = "";
         }
      
         break;
       case estDISPARADO:
         
         break;
     }
  }
  
  if (estado != estadoAnt) {
     switch (estado) { 
       case estDESATIVADO:
         lcd.clear();
         lcd.print("   DESATIVADO");
         break;
       case estATIVAR:
         lcd.clear();
         lcd.print("ATIVANDO...");
         break;
       case estATIVADO:
         lcd.clear();
         lcd.print("    ATIVADO");
         zonas = "";
         break;
       case estDISPARADO:
         lcd.clear();
         lcd.print("   DISPARADO");  
         lcd.setCursor(0, 1);
         lcd.print("zonas: " + zonas); 
         break;
     }
  }
  estadoAnt = estado;
  
  if ((estado == estATIVAR) || (estado == estDISPARADO)) { 
    if (bitRead(millis(), 8)) {
       lcd.display();
    } else {
       lcd.noDisplay();
    }
  } else {
    lcd.display();
  }
  
  delay(20);
}
