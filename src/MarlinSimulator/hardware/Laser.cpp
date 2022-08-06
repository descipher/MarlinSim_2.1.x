#include <imgui.h>
#include "pinmapping.h"
#include "Laser.h"


Laser::Laser(pin_type laser_pin, pwm_data pwm_parms) : VirtualPrinter::Component("Laser"), laser_pin(laser_pin), pwm_parms(pwm_parms) {
  Gpio::attach(this->laser_pin, [this](GpioEvent& event){ this->interrupt(event); });
}

Laser::~Laser() {
}

void Laser::update() {
  pwm_parms.pwm_duty = Gpio::get_pin_value(laser_pin);
  pwm_parms.pwm_pin = SPINDLE_LASER_PWM_PIN;
  pwm_parms.pwm_period = 1/SPINDLE_LASER_FREQUENCY;
}

void Laser::ui_widget() {
  //ImGui::Text("Frequency: %n", pwm_frequency);
  ImGui::Text("Laser Pin: %d", pwm_parms.pwm_pin);
  ImGui::Text("Laser Duty: %d", pwm_parms.pwm_duty);
  ImGui::Text("Laser Period: %f", pwm_parms.pwm_period);
  ImGui::Text("Laser PWM Update: %f", pwm_parms.pwm_last_update);
}

void Laser::interrupt(GpioEvent& ev) {
    // always update the pwm
  double time_delta = Kernel::TimeControl::ticksToNanos(ev.timestamp - pwm_parms.pwm_last_update) / (double)Kernel::TimeControl::ONE_BILLION;
  pwm_parms.pwm_last_update = ev.timestamp;
  // if (ev.event == ev.RISE && ev.pin_id == pwm_parms.pwm_pin) {
  //    if (pwm_parms.pwm_hightick) pwm_parms.pwm_period = ev.timestamp - pwm_parms.pwm_hightick;
  //    pwm_parms.pwm_hightick = ev.timestamp;
  // } else if ( ev.event == ev.FALL && ev.pin_id == pwm_parms.pwm_pin) {
  //    pwm_parms.pwm_lowtick = ev.timestamp;
  //    pwm_parms.pwm_duty = ev.timestamp - pwm_parms.pwm_hightick;
  // }
}