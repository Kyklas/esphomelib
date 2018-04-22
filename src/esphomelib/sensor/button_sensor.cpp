

#include "button_sensor.h"

namespace esphomelib {

namespace button_sensor {

static const char *TAG = "button_sensor";


const std::string ButtonSensor::GetStateName(BUTTON_STATE state)
{
	switch(state)
	{
	case BUTTON_OFF:
		return std::string("OFF");
	case BUTTON_PRESSED:
		return std::string("PRESSED");
	case BUTTON_ON:
		return std::string("ON");
	case BUTTON_RELEASED:
		return std::string("RELEASED");
	default :
		return std::string("Unknown");
	}
}


void ButtonSensor::set_on_new_state_callback(button_callback_t callback) {
  this->new_state_callback_ = std::move(callback);
}


void ButtonSensor::set_on_new_state_str_callback(sensor::sensor_str_callback_t callback) {
	this->new_state_str_callback_ = std::move(callback);
}


void ButtonSensor::publish_state(BUTTON_STATE state) {
	if(this->new_state_callback_ != NULL)
		this->new_state_callback_(state);
	if(this->new_state_str_callback_ != NULL)
	{
		this->new_state_str_callback_(GetStateName(state));
	}
}

BUTTON_STATE ButtonSensor::Get_State()
{
	return state_;
}

ButtonSensor::ButtonSensor() : new_state_callback_(NULL), new_state_str_callback_(NULL), state_(BUTTON_OFF) {};

} // namespace binary_sensor

} // namespace esphomelib
