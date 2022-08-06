#pragma once
#include <cmath>
#include "Gpio.h"
#include "../virtual_printer.h"


struct pwm_data {
  uint8_t pwm_pin;   
  uint64_t pwm_period;
  uint64_t pwm_duty;
  uint64_t pwm_hightick;
  uint64_t pwm_lowtick;
  uint64_t pwm_last_update;
};

class Laser: public VirtualPrinter::Component {
public:

  pin_type laser_pin;
  pwm_data pwm_parms;

  Laser(pin_type laser_pin, pwm_data pwm_parms);
  virtual ~Laser();
  void interrupt(GpioEvent& ev);
  void update();
  void ui_widget();
  
};
