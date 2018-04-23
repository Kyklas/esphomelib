//
// Created by Otto Winter on 26.11.17.
//

#ifndef ESPHOMELIB_INPUT_GPIO_BUTTON_SENSOR_COMPONENT_H
#define ESPHOMELIB_INPUT_GPIO_BUTTON_SENSOR_COMPONENT_H

#include <esp32-hal-gpio.h>
#include "esphomelib/sensor/button_sensor.h"
#include <cstdint>

namespace esphomelib {

namespace input {

/// GPIOBinarySensorComponent - Simple binary_sensor component for a GPIO pin.
class GPIOButtonSensorComponent : public button_sensor::ButtonSensor, public Component {
 public:
  /** Construct a GPIOBinarySensorComponent.
   *
   * @param pin The pin number.
   * @param mode The pin-mode.
   */
  explicit GPIOButtonSensorComponent(uint8_t pin, uint8_t mode = INPUT);

  uint8_t get_pin() const;
  void set_pin(uint8_t pin);

  uint8_t get_mode() const;
  /// Set the pinMode - for example INPUT.
  void set_mode(uint8_t mode);

  bool is_inverted() const;
  void set_inverted(bool inverted);

  void setup() override;
  float get_setup_priority() const override;
  void loop() override;

 protected:
  uint8_t pin_;
  uint8_t mode_;
  bool inverted_;
  bool first_run_;
  button_sensor::BUTTON_STATE last_state_;
};

} // namespace input

} // namespace esphomelib

#endif //ESPHOMELIB_INPUT_GPIO_BINARY_SENSOR_COMPONENT_H
