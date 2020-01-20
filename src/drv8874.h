#ifndef SITRON_DRV8874_H
#define SITRON_DRV8874_H

/* C library */
#include <errno.h>
#include <stdint.h>

/* */
enum drv8874_direction {
	DRV8874_DIRECTION_FORWARD = -1,
	DRV8874_DIRECTION_BACKWARD = 1,
};

/* */
class DRV8874 {

	public:
		DRV8874(const uint8_t pin_sleep, const uint8_t pin_pmode, const uint8_t pin_in1, const uint8_t pin_in2, const uint8_t pin_imode, const uint8_t pin_iprop, const float aref, const float riprop);
		int drive(const enum drv8874_direction dir, const float speed);
		int get_current(float * const current);
		~DRV8874();

	private:
		uint8_t pin_sleep;
		uint8_t pin_pmode;
		uint8_t pin_in1;
		uint8_t pin_in2;
		uint8_t pin_imode;
		uint8_t pin_iprop;
		float aref;
		float riprop;
};

#endif /* !SITRON_DRV8874_H */
