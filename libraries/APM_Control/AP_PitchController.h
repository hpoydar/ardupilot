// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_PITCH_CONTROLLER_H__
#define __AP_PITCH_CONTROLLER_H__

#include <AP_AHRS.h>
#include <AP_Common.h>
#include <AP_SpdHgtControl.h>
#include <math.h>

class AP_PitchController {
public:
	AP_PitchController(const AP_SpdHgtControl::AircraftParameters &parms) :
		aparm(parms)
    { 
		AP_Param::setup_object_defaults(this, var_info);
	}

	void set_ahrs(AP_AHRS *ahrs) { _ahrs = ahrs; }

	int32_t get_rate_out(float desired_rate, float scaler);
	int32_t get_servo_out(int32_t angle_err, float scaler, bool stabilize);
    float   get_coordination_rate_offset(void) const;

	void reset_I();

	static const struct AP_Param::GroupInfo var_info[];

private:
	const AP_SpdHgtControl::AircraftParameters &aparm;
	AP_Float _tau;
	AP_Float _K_P;
	AP_Float _K_I;
	AP_Float _K_D;
	AP_Int16 _max_rate_pos;
	AP_Int16 _max_rate_neg;
	AP_Float _roll_ff;
    AP_Int16  _imax;
	uint32_t _last_t;
	float _last_out;
	
	float _integrator;

	int32_t _get_rate_out(float desired_rate, float scaler, bool stabilize, float aspeed);
    float   _get_coordination_rate_offset(float &aspeed, bool &inverted) const;
	
	AP_AHRS *_ahrs;
	
};

#endif // __AP_PITCH_CONTROLLER_H__
