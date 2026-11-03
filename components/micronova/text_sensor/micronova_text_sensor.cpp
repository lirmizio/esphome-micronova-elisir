#include "micronova_text_sensor.h"

namespace esphome::micronova {

static const char *const TAG = "micronova.text_sensor";

void MicroNovaTextSensor::dump_config() {
  LOG_TEXT_SENSOR("", "Micronova text sensor", this);
  this->dump_base_config();
}

void MicroNovaTextSensor::process_value_from_stove(int value_from_stove) {
  if (value_from_stove == -1) {
    this->publish_state("unknown");
    return;
  }
  // The table has 11 entries; any other code from the board would read past it.
  if (value_from_stove > 10) {
    this->publish_state("Codice " + to_string(value_from_stove));
    return;
  }

  this->publish_state(STOVE_STATES[value_from_stove]);
}

}  // namespace esphome::micronova
