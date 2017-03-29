/*
 * I2CPWM.h
 *
 *  Created on: 10 dic. 2016
 *      Author: oscar
 *  Changes v0.1: 29 mar. 2017
 */

#ifndef I2CPWM_H_
#define I2CPWM_H_

//Número de servos en la placa
#define NUMBER_OF_SERVOS 16

//Máximo y mínimo
#define MINIMUM_PWM 150
#define MAXIMUM_PWM 550

//NO TOCAR
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
//NO TOCAR

#include <Arduino.h>

class I2CPWM{
public:

	/* FUNCIONES DISPONIBLES */

	 //Crea un objeto I2CPWM, dar la dirección, depende de los jumpers cortados
	I2CPWM(uint8_t address = 0x40);

  	//Esta función debe llamarse en el setup
  	void init();

	//Conecta un servo, especifica el canal. Opcionalmente pon un máximo y un mínimo (0-180).
	//Opcionalmente especifica si los ángulos deben ser en sentido opuesto
	void attach(uint8_t servo, uint16_t minimum = 0, uint16_t maximum = 180, bool isReverse = false);

	//Mueve el canal especificado a una nueva posición
	void write(uint8_t servo, uint16_t angle);

	//Devuelve la posición objetivo del canal especificado
	uint16_t getTarget(uint8_t servo);

	/* FUNCIONES DISPONIBLES */


private:

	void setPWMFreq(float freq);

	void setPWM(uint8_t num, uint16_t on, uint16_t off);

	uint8_t read8(uint8_t addr);

	void write8(uint8_t addr, uint8_t d);

	void reset(void);

	uint8_t _address;
	uint16_t * target;
	uint16_t * mins;
	uint16_t * maxs;
	bool * reverse;
};

#endif /* I2CPWM_H_ */
