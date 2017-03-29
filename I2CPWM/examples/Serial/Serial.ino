#include "Arduino.h"
#include "I2CPWM.h"

/* Este Sketch sirve para controlar los servos por Serial e ir probando posiciones
   Se introduce el numero del servo se deja un espacio y se pone en ángulo y se da enter
   Si queremos mover el servo 8 a 120º ponemos: "8 120" y de damos a enter
*/

//CONEXIONADO
//GND - GND
//OE - NO CONECTAR
//SCL - A5
//SDA - A4
//VCC - 5V
//V+ - NO CONECTAR
//CLEMA V+ - POTENCIA+
//CLEMA GND - POTENCIA-


//Declaramos el objeto del PCA9685 (Placa de Servos)
//El parámetro es la dirección de la placa (Hay unos jumpers para cambiarla)
//Se debe crear uno de estos por placa que se use, evidentemente no pueden compartir dirección
I2CPWM placaServos(0x40);

void setup() {
  Serial.begin(9600);

  //Hay que llamar en el setup a esta función
  placaServos.init();

  //Enganchamos los 16 servos
  for (int i = 0; i < 16; i++) {
    placaServos.attach(i); //Si omito parametros por defecto serán (0-180º) y false para la dirección
    placaServos.write(i, 90); //Movemos a 90º cada servo
  }
}

long int timer = millis(); //Esto lo usaremos para sacar por pantalla posiciones

void loop() {
  //Si se introduce algo por serial
  if (Serial.available() > 0) {
    //Leer el número escrito por serial para el servo
    int servo = String(Serial.readStringUntil(' ')).toInt();
    //Leer el número escrito por serial para el ángulo
    int angulo = String(Serial.readStringUntil('\n')).toInt();
    //Mover el servo elegido a la posición elegida
    placaServos.write(servo, angulo);
  }

  //Cada segundo hacemos lo siguiente
  if (millis() - timer > 1000) {
    //Cogemos la posición de cada servo con getTarget(servo) [da la posición a la que va, no necesariamente en
    //la que está ahora mismo. Ponemos un espacio tras el número
    for (int i = 0; i < 16; i++) {
      Serial.print(String(placaServos.getTarget(i)) + " ");
    }
    //Ponemos un salto de línea
    Serial.println();
    //Actualizamos el contador
    timer = millis();
  }
}

