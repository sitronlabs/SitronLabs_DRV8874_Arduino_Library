/* Self header */
#include "drv8874.h"

/* Arduino library */
#include "Arduino.h"

DRV8874::DRV8874(const uint8_t pin_sleep, const uint8_t pin_pmode, const uint8_t pin_in1, const uint8_t pin_in2, const uint8_t pin_imode, const uint8_t pin_iprop, const float aref, const float riprop) {

	/* Save configuration values */
	this->pin_sleep = pin_sleep;
	this->pin_pmode = pin_pmode;
	this->pin_in1 = pin_in1;
	this->pin_in2 = pin_in2;
	this->pin_imode = pin_imode;
	this->pin_iprop = pin_iprop;
	this->aref = aref;
	this->riprop = riprop;

	/* Set h-bridge in high impedance mode */
	pinMode(this->pin_in1, OUTPUT);
	pinMode(this->pin_in2, OUTPUT);
	digitalWrite(this->pin_in1, 0);
	digitalWrite(this->pin_in2, 0);

	/* Set device in pwm mode */
	pinMode(this->pin_sleep, OUTPUT);
	digitalWrite(this->pin_sleep, 0);
	delay(1);
	pinMode(this->pin_pmode, OUTPUT);
	digitalWrite(this->pin_pmode, 1);
	digitalWrite(this->pin_sleep, 1);
}

int DRV8874::drive(const enum drv8874_direction dir, const float speed) {

	/* Ensure input parameters are valid */
	if (speed < 0 || speed > 1) return -EINVAL;
	if (dir != DRV8874_DIRECTION_FORWARD && dir != DRV8874_DIRECTION_BACKWARD) return -EINVAL;

	/* Adjust direction and speed */
	if (dir == DRV8874_DIRECTION_BACKWARD) {
		digitalWrite(this->pin_in1, 1);
		analogWrite(this->pin_in2, 255 - (255 * speed));
	} else {
		analogWrite(this->pin_in1, 255 - (255 * speed));
		digitalWrite(this->pin_in2, 1);
	}

	/* Return success */
	return 0;
}

int DRV8874::get_current(float * const current) {

	/* Ensure input parameters are valid */
	if (current == NULL) return -EINVAL;

	/* Compute current */
	float viprop = (this->aref * analogRead(this->pin_iprop)) / 1023;
	float iprop = viprop / this->riprop;
	*current = (2197.8) * iprop;

	/* Return success */
	return 0;
}

DRV8874::~DRV8874() {

	/* Reconfigure pins */
	pinMode(this->pin_sleep, INPUT);
	pinMode(this->pin_pmode, INPUT);
	pinMode(this->pin_in1, INPUT);
	pinMode(this->pin_in2, INPUT);
}
