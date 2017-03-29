#include "Arduino.h"
#include "I2CPWM.h"

//CONEXIONADO
//GND - GND
//OE - NO CONECTAR
//SCL - A5
//SDA - A4
//VCC - 5V
//V+ - NO CONECTAR
//CLEMA V+ - POTENCIA+
//CLEMA GND - POTENCIA-

/* Este Sketch mueve los servos conectados a los canales 0 y 1 de un lado a otro */

//Declaramos el objeto del PCA9685 (Placa de Servos)
//El parámetro es la dirección de la placa (Hay unos jumpers para cambiarla)
//Se debe crear uno de estos por placa que se use, evidentemente no pueden compartir dirección
I2CPWM placaServos(0x40);

void setup() {
  //Hay que llamar en el setup a esta función
  placaServos.init();

  //Con esto especificamos que vamos a usar un canal, el primer valor es el canal al que se conecta el servo
  //El segundo es el ángulo mínimo (0-180) y el tercero el ángulo máximo.
  //El cuarto es la dirección de recorrido, en sentido horario o antihorario
  placaServos.attach(0, 0, 180, false);

  //Además usaremos el canal 1 de 0º a 90º y en sentido opuesto al anterior.
  placaServos.attach(1, 0, 90, true);
}

void loop() {
  //Primero haremos el recorrido en una dirección
  for (int pos = 0; pos <= 180; pos++) {

    placaServos.write(0, pos); //Movemos el servo 0
    delay(5); //Esperamos un poco entre movimientos

    //Movemos el servo 1 (Como hemos puesto que 0º y 90º son los límites,
    //no funcionará hasta que estemos dentro de ellos)
    placaServos.write(1, pos);
    delay(5); //Esperamos un poco entre movimientos
  }

  //Ahora vamos en la otra dirección
  for (int pos = 180; pos > 0; pos--) {
    placaServos.write(0, pos);
    delay(5);
    placaServos.write(1, pos);
    delay(5);
  }
}
