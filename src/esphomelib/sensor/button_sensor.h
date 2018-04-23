
#ifndef ESPHOMELIB_BUTTON_SENSOR_BINARY_SENSOR_H
#define ESPHOMELIB_BUTTON_SENSOR_BINARY_SENSOR_H

#include "esphomelib/component.h"
#include "sensor.h"

namespace esphomelib {

namespace button_sensor {

typedef enum BUTTON_STATE{
	BUTTON_OFF,
	BUTTON_PRESSED,
	BUTTON_ON,
	BUTTON_RELEASED,
}BUTTON_STATE;

/// typedef for binary_sensor callbacks. First parameter is new value.
using button_callback_t = std::function<void(BUTTON_STATE)>;

/** Base class for all binary_sensor-type classes.
 *
 * This class includes a callback that components such as MQTT can subscribe to for state changes.
 * The sub classes should notify the front-end of new states via the publish_state() method which
 * handles inverted inputs for you.
 */
class ButtonSensor : public sensor::Sensor {
 public:
	ButtonSensor();

	virtual std::string unit_of_measurement() {return std::string(); };

  /** Set callback for state changes.
   *
   * @param callback The void(bool) callback.
   */
	virtual void set_on_new_state_callback(button_callback_t callback);
	virtual void set_on_new_state_str_callback(sensor::sensor_str_callback_t callback);

  /** Publish a new state.
   *
   * Inverted input is handled by this method and sub-classes don't need to worry about inverting themselves.
   *
   * @param state The new state.
   */
  virtual void publish_state(BUTTON_STATE state);

  BUTTON_STATE Get_State();

  static const std::string GetStateName(BUTTON_STATE state);

 protected:
  button_callback_t new_state_callback_;
  sensor::sensor_str_callback_t new_state_str_callback_;

  BUTTON_STATE state_;


};

} // namespace button_sensor

} // namespace esphomelib

#endif //ESPHOMELIB_BUTTON_SENSOR_BINARY_SENSOR_H
