/*
 * rmt_output_component.cpp
 *
 *  Created on: Mar 10, 2018
 *      Author: stan
 */


#include <esp_log.h>
#include "rmt_output_component.h"
#include "ir_transmitter_component.h"

namespace esphomelib {

namespace output {

static const char *TAG = "output::rmt";

RMTOutputComponent::RMTOutputComponent(uint8_t pin, const LedType& type, int count)
    : Component(), HighPowerOutput(),pin_(pin),count_(count), pLed_(NULL), type_(type),updated_(false) {
	  this->set_channel(next_rmt_channel);
	  next_rmt_channel = rmt_channel_t(int(next_rmt_channel) + 2); // NOLINT
	  color_.value = 0;
}


void RMTOutputComponent::setup() {
  ESP_LOGD(TAG, "Setting up RMTComponent with pin=%u, channel=%u, count=%u",
           this->pin_, this->channel_,this->count_ );

  pLed_ = new SmartLed(type_,count_,pin_,channel_, DoubleBuffer );

  if(pLed_ != NULL)
  {
	  if(get_atx() == NULL)
	  {
		  set_color(Rgb{0,0,0});
		  Update();
	  }
	  // disable ATX
  }
  else
  {
	  ESP_LOGE(TAG, "Setting up RMTComponent Failed");
  }
}

float RMTOutputComponent::get_setup_priority() const {
  return setup_priority::HARDWARE;
}

uint8_t RMTOutputComponent::get_pin() const {
  return this->pin_;
}
void RMTOutputComponent::set_pin(uint8_t pin) {
  assert_construction_state(this);
  assert_is_pin(pin);
  this->pin_ = pin;
}
uint8_t RMTOutputComponent::get_channel() const {
  return this->channel_;
}
void RMTOutputComponent::set_channel(uint8_t channel) {
  assert_construction_state(this);
  assert(channel < 8);
  this->channel_ = channel;
}
uint8_t RMTOutputComponent::get_count() const {
  return this->count_;
}
void RMTOutputComponent::set_count(uint8_t count) {
  assert_construction_state(this);
  this->count_ = count;
}

void RMTOutputComponent::set_color(Rgb color){
	if(color.value != color_.value)
	{
//		ESP_LOGI(TAG, "Set_color %08X",color.value);
		updated_ = false; // update is required
		color_ = color;
	}
}

void RMTOutputComponent::Update()
{
	static uint32_t time = millis();

  // this may need to be called every loop
  if ( color_.value != 0)
	  this->enable_atx();

//	// Update greater than 10ms apart
//	if(millis() - time < 10)
//		return;

	  if(pLed_ != NULL && !updated_)
	  {
		  time = millis();
		  updated_=true;
		  for(uint8_t idx = 0; idx < count_ ; idx++)
		  {
			  (*pLed_)[idx] = color_;
		  }
		  pLed_->show();
//			ESP_LOGI(TAG, "Show RGB %08X",color_.value);
//		   should there be a wait ?
			  pLed_->wait();
			  usleep(5000);
	  }

}


}

}
