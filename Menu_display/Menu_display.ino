#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ======= MAPEAMENTO DE HARDWARE =======
#define butUp     12
#define butDown   11
#define butP      10
#define butM      8
#define Lamp1     A0
#define Lamp2     A1
#define pwmOut    3

// ======= PROTÓTIPO DE FUNÇÕES AUXILIARES =======
void changeMenu();
void dispMenu();
void data_hora();
void temperatura();
void lights();
void menu4();

// ======= VARIÁVEIS GLOBAIS =======
int pwm = 0x00;
char menu = 0x01;                                     //Variável para selecionar o menu
char set1 = 0x00, set2 = 0x00;                        //Controle de lampadas
boolean t_butUp, t_butDown, t_butP, t_butM;           //Flags para armazenar o estado dos botões

// ======= HARDWARE DO LCD =======
LiquidCrystal_I2C disp(0x27, 16, 2);



void setup() {
  disp.begin(16,2);

  for(char i=10; i<13; i++) pinMode(i, INPUT_PULLUP);  //Entrada de botões(digitais 9 a 12)
  pinMode(butM, INPUT_PULLUP);
  pinMode(pwmOut, OUTPUT);
  pinMode(Lamp1, OUTPUT);
  pinMode(Lamp2, OUTPUT);

  //Limpandos as flags
  t_butUp   = 0x00;
  t_butDown = 0x00;
  t_butP    = 0x00;
  t_butM    = 0x00;
 
  digitalWrite(Lamp1, LOW);                          
  digitalWrite(Lamp2, LOW);                          
}

void loop() {
  changeMenu();
  dispMenu();

} //End Loop

void changeMenu(){
  if(!digitalRead(butUp))   t_butUp   = 0x01;        //Botao up pressionado? Seta flag
  if(!digitalRead(butDown)) t_butDown = 0x01;        
 
  if(digitalRead(butUp) && t_butUp){                 //Botao up solto e flag setada?
    t_butUp = 0x00;                                  //Limpa a flag

    disp.clear();                                    
    menu++;                                          

    if(menu > 0x04) menu = 0x01;                     
  } //End butUp

  if(digitalRead(butDown) && t_butDown){              
    t_butDown = 0x00;                                 

    disp.clear();                                    
    menu--;                                          

    if(menu < 0x01) menu = 0x04;                    
  } //End butDown
 
} //End changeMenu

void dispMenu(){                                     
  switch(menu){                                      
   
    case 0x01:                                      
      data_hora();                                   
      break;
     
    case 0x02:
      temperatura();
      break;

    case 0x03:
      lights();
      break;

    case 0x04:
      menu04();
      break;
  } //End switch
 
} //End dispMenu

void data_hora(){
  disp.setCursor(0,0);                              
  disp.print("Data e Hora");
  disp.setCursor(0,1);                              

  disp.print("03/06/2020  11:24");
}//End data_Hota

void temperatura(){
  disp.setCursor(0,0);
  disp.print("Temperatura");
  disp.setCursor(1,1);

  disp.print("25 Celsius");
} //End temperatura

void lights(){
  disp.setCursor(0,0);
  disp.print("Acionar Lampadas");

  if(!digitalRead(butP)) t_butP = 0x01;         
  if(!digitalRead(butM)) t_butM = 0x01;           

  if(digitalRead(butP) && t_butP){               
    t_butP = 0x00;

    set1++;

    if(set1 > 2) set1 = 0x01;                     

    switch(set1){
      case 0x01:
        disp.setCursor(0,1);                     
        disp.print("L1 on ");                    
        digitalWrite(Lamp1, HIGH);         
        break;

       case 0x02:
        disp.setCursor(0,1);                     
        disp.print("L1 off");                    
        digitalWrite(Lamp1, LOW);                
        break;
    } //End switch set1    
  } //End butP

  if(digitalRead(butM) && t_butM){                //Botão solto e flag setada?
    t_butM = 0x00;

    set2++;

    if(set2 > 2) set2 = 0x01;                   
  //disp.clear();

    switch(set2){
      case 0x01:
        disp.setCursor(8,1);                     
        disp.print("L2 on ");                    
        digitalWrite(Lamp2, HIGH);               
        break;

       case 0x02:
        disp.setCursor(8,1);                    
        disp.print("L2 off");                    
        digitalWrite(Lamp2, LOW);                
        break;
    } //End switch set2    
  } //End butM
 
} //End lights



void menu04(){
  disp.setCursor(0,0);
  disp.print("Controle PWM");

  if(!digitalRead(butP))  t_butP = 0x01;
  if(!digitalRead(butM))  t_butM = 0x01;

  if(digitalRead(butP) && t_butP){              //Se não estiver apertado e a flag for 1
    t_butP = 0x00;  
    pwm++;

    if(pwm > 255) pwm = 0;                      //Quando chegar no valor maximo, volta pra zero
    disp.clear();
    analogWrite(pwmOut, pwm);
  }//End butP


  if(digitalRead(butM) && t_butM){              //Se não estiver apertado e a flag for 1
    t_butM = 0x00;  
    pwm--;

    if(pwm < 0) pwm = 255;                     //Quando chegar no valor maximo, volta pra zero
    disp.clear();
    analogWrite(pwmOut, pwm);
  }//End butM
 
    disp.setCursor(0,1);
    disp.print("PWM: " + String(pwm));                //Imprime valor de pwm no display. OBS: PRECISAMOS CONVERTER O VALOW DE PWM EM STRING PARA QUE ELE POSSA SER CONCATENADO E APARECER NO DISPLAY. SEM ISSO ELE NAO PRINTA O VALOR.
} //End menu04 
