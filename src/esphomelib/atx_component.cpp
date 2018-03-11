//
// Created by Otto Winter on 25.11.17.
//

#include <esp_log.h>
#include <esp32-hal.h>
#include "atx_component.h"

namespace esphomelib {

static const char *TAG = "atx";

void esphomelib::ATXComponent::setup() {
  ESP_LOGD(TAG, "Setting up ATX...");
  ESP_LOGV(TAG, "    Pin: %u", this->pin_);

  pinMode(this->pin_, OUTPUT);
  set_value(LOW); // OFF
  this->enabled_ = false;
}

float esphomelib::ATXComponent::get_setup_priority() const {
  return setup_priority::HARDWARE + 1.0f;
}

esphomelib::ATXComponent::ATXComponent(uint8_t pin, uint32_t enable_time, uint32_t keep_on_time, bool active_low)
    : pin_(pin), enabled_(false), enable_time_(enable_time), keep_on_time_(keep_on_time),active_low_(active_low) {}

bool esphomelib::ATXComponent::is_enabled() const {
  return this->enabled_;
}

void esphomelib::ATXComponent::enable() {
  this->cancel_timeout("atx-off");

  set_value(HIGH); // ON

  if (!this->enabled_) {
    ESP_LOGI(TAG, "Enabling ATX.");
    delay(this->enable_time_);
    this->enabled_ = true;
  }

  this->set_timeout("atx-off", this->keep_on_time_, [&]() {
    ESP_LOGI(TAG, "Disabling ATX.");
    set_value(LOW); // OFF
    this->enabled_ = false;
  });
}
uint8_t ATXComponent::get_pin() const {
  return this->pin_;
}
void ATXComponent::set_pin(uint8_t pin) {
  assert_construction_state(this);
  assert_is_pin(pin);
  this->pin_ = pin;
}
uint32_t ATXComponent::get_enable_time() const {
  return this->enable_time_;
}
void ATXComponent::set_enable_time(uint32_t enable_time) {
  this->enable_time_ = enable_time;
}
uint32_t ATXComponent::get_keep_on_time() const {
  return this->keep_on_time_;
}
void ATXComponent::set_keep_on_time(uint32_t keep_on_time) {
  this->keep_on_time_ = keep_on_time;
}

void ATXComponent::set_active_low(bool polarity){
	this->active_low_ = polarity;
}

void ATXComponent::set_value(bool active){
	digitalWrite(this->pin_, active_low_?!active:active);
}

} // namespace esphomelib
