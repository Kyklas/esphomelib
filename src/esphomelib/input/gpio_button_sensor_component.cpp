//
// Created by Otto Winter on 26.11.17.
//

#include <esp32-hal-gpio.h>
#include "gpio_button_sensor_component.h"

namespace esphomelib {

namespace input {

void GPIOButtonSensorComponent::setup() {
  pinMode(this->pin_, this->mode_);
}

void GPIOButtonSensorComponent::loop() {
  auto value = bool(digitalRead(this->pin_));

	if(value != inverted_)
	{
	  // Button Pressed
	  switch(state_)
	  {
	  case button_sensor::BUTTON_OFF:
		  state_ = button_sensor::BUTTON_PRESSED;
		  break;
	  case button_sensor::BUTTON_PRESSED:
		  state_ = button_sensor::BUTTON_ON;
		  break;
	  case button_sensor::BUTTON_RELEASED:
		  state_ = button_sensor::BUTTON_PRESSED;
		  break;
	  }
	}
	else
	{
	  // Button Released
	  switch(state_)
	  {
	  case button_sensor::BUTTON_ON:
		  state_ = button_sensor::BUTTON_RELEASED;
		  break;
	  case button_sensor::BUTTON_PRESSED:
		  state_ = button_sensor::BUTTON_RELEASED;
		  break;
	  case button_sensor::BUTTON_RELEASED:
		  state_ = button_sensor::BUTTON_OFF;
		  break;
	  }
	}

  if (this->first_run_ || state_ != this->last_state_) {
    this->first_run_ = false;
    this->last_state_ = state_;
    this->publish_state(state_);
  }
}

float GPIOButtonSensorComponent::get_setup_priority() const {
  return setup_priority::HARDWARE;
}

GPIOButtonSensorComponent::GPIOButtonSensorComponent(uint8_t pin, uint8_t mode)
    : ButtonSensor(), mode_(mode), first_run_(true), last_state_(button_sensor::BUTTON_OFF),inverted_(0) {
  this->set_pin(pin);
}

uint8_t GPIOButtonSensorComponent::get_pin() const {
  return this->pin_;
}
void GPIOButtonSensorComponent::set_pin(uint8_t pin) {
  assert_is_pin(pin);
  assert_construction_state(this);
  this->pin_ = pin;
}
uint8_t GPIOButtonSensorComponent::get_mode() const {
  return this->mode_;
}
void GPIOButtonSensorComponent::set_mode(uint8_t mode) {
  assert_construction_state(this);
  this->mode_ = mode;
}

bool GPIOButtonSensorComponent::is_inverted() const {
  return this->inverted_;
}
void GPIOButtonSensorComponent::set_inverted(bool inverted) {
  this->inverted_ = inverted;
}

} // namespace input

} // namespace esphomelib
