/*
 * rmt_output_component.h
 *
 *  Created on: Mar 10, 2018
 *      Author: stan
 */


#ifndef ESPHOMELIB_OUTPUT_RMT_OUTPUT_COMPONENT_H
#define ESPHOMELIB_OUTPUT_RMT_OUTPUT_COMPONENT_H

#define USE_SPI_DEV 1

#include <SmartLeds.h>
#include "high_power_output.h"

namespace esphomelib {

namespace output {

/// ESP32 RMT output component.
class RMTOutputComponent : public HighPowerOutput, public Component {
 public:
  /// Construct a LEDCOutputComponent. The channel will be set using the next_ledc_channel global variable.
  explicit RMTOutputComponent(uint8_t pin, const LedType& type, int count);

  uint8_t get_pin() const;
  void set_pin(uint8_t pin);
  uint8_t get_channel() const;
  void set_channel(uint8_t channel);
  uint8_t get_count() const;
  void set_count(uint8_t count);

  void setup() override;
  float get_setup_priority() const override;

  void set_color(Rgb color);
  void Update();

 protected:
  uint8_t pin_;
  uint8_t channel_;
  uint8_t count_;
  LedType type_;
  Rgb color_;
  bool updated_;

#if USE_RMT_DEV
  SmartLed* pLed_;
#elif USE_SPI_DEV
  WS2812B * pLed_;
#endif
};


} // namespace output

} // namespace esphomelib




#endif /* ESPHOMELIB_OUTPUT_RMT_OUTPUT_COMPONENT_H */
