//App usado: Bluetooth RC Car

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

int l1a = 15;
int l1b = 2;
int l2a = 4;
int l2b = 16;

BluetoothSerial SerialBT;
char recebido;
void setup() {
  pinMode(l1a, OUTPUT);
  pinMode(l1b, OUTPUT);
  pinMode(l2a, OUTPUT);
  pinMode(l2b, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32"); 
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    recebido = SerialBT.read();
    Serial.write(recebido);
  }
  delay(20);

/*
  F = Frente
  B = Trás
  L = Esquerda
  R = Direita

*/
  if(recebido == 'F'){
    digitalWrite(l1a, HIGH);
    digitalWrite(l1b, LOW);
    digitalWrite(l2a, HIGH);
    digitalWrite(l2b, LOW);
    }else if(recebido == 'B'){
      digitalWrite(l1a, LOW);
      digitalWrite(l1b, HIGH);
      digitalWrite(l2a, LOW);
      digitalWrite(l2b, HIGH);
    }else if(recebido == 'L'){
      digitalWrite(l1a, LOW);
      digitalWrite(l1b, LOW);
      digitalWrite(l2a, HIGH);
      digitalWrite(l2b, LOW);
    }else if(recebido == 'R'){
      digitalWrite(l1a, LOW);
      digitalWrite(l1b, HIGH);
      digitalWrite(l2a, LOW);
      digitalWrite(l2b, LOW);
    }

}
