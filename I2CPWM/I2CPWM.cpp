/*
 * I2CPWM.cpp
 *
 *  Created on: 10 dic. 2016
 *      Author: oscar
 *  Changes v0.1: 29 mar. 2017
 */

#include "I2CPWM.h"
#include <Wire.h>

I2CPWM::I2CPWM(uint8_t address) {
	_address = address;
	target = new uint16_t[NUMBER_OF_SERVOS];
	mins = new uint16_t[NUMBER_OF_SERVOS];
	maxs = new uint16_t[NUMBER_OF_SERVOS];
	reverse = new bool[NUMBER_OF_SERVOS];
}

void I2CPWM::init() {
  Wire.begin();
  reset();

  setPWMFreq(60);
  yield();
}

void I2CPWM::attach(uint8_t servo, uint16_t minimum, uint16_t maximum,
		bool isReverse) {
	mins[servo] = minimum;
	maxs[servo] = maximum;
	reverse[servo] = isReverse;
}

void I2CPWM::write(uint8_t servo, uint16_t angle) {
	angle = constrain(angle, mins[servo], maxs[servo]);
	target[servo] = angle;
	if (reverse[servo]) {
		setPWM(servo, 0, map(angle, 0, 180, MINIMUM_PWM, MAXIMUM_PWM));
	} else {
		setPWM(servo, 0, map(angle, 0, 180, MAXIMUM_PWM, MINIMUM_PWM));
	}
}

uint16_t I2CPWM::getTarget(uint8_t servo) {
	return target[servo];
}

void I2CPWM::setPWMFreq(float freq) {
	freq *= 0.9;
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	uint8_t prescale = floor(prescaleval + 0.5);

	uint8_t oldmode = read8(PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;
	write8(PCA9685_MODE1, newmode);
	write8(PCA9685_PRESCALE, prescale);
	write8(PCA9685_MODE1, oldmode);
	delay(5);
	write8(PCA9685_MODE1, oldmode | 0xa1);
}

void I2CPWM::setPWM(uint8_t num, uint16_t on, uint16_t off) {
	Wire.beginTransmission(_address);
	Wire.write(LED0_ON_L + 4 * num);
	Wire.write(on);
	Wire.write(on >> 8);
	Wire.write(off);
	Wire.write(off >> 8);
	Wire.endTransmission();
}

uint8_t I2CPWM::read8(uint8_t addr) {
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.endTransmission();

	Wire.requestFrom((uint8_t) _address, (uint8_t) 1);
	return Wire.read();
}
void I2CPWM::write8(uint8_t addr, uint8_t d) {
	Wire.beginTransmission(_address);
	Wire.write(addr);
	Wire.write(d);
	Wire.endTransmission();
}
void I2CPWM::reset(void) {
	write8(PCA9685_MODE1, 0x0);
}
