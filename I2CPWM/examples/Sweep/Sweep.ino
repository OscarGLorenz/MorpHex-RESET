#include "Arduino.h"
#include "I2CPWM.h"

I2CPWM i2cPWM(0x40);

int pos = 0;
const int servo = 9;

void setup() {
	i2cPWM.attach(servo);
}

void loop() {
	for (pos = 0; pos <= 180; pos += 1) { 
		i2cPWM.write(servo, pos); 
		delay(15);   
	}
	for (pos = 180; pos >= 0; pos -= 1) { 
		i2cPWM.write(servo, pos);
		delay(15);
	}
}
