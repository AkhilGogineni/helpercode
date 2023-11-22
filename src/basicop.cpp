#include "main.h"
#include <fstream>

using namespace std;

void wait(int sec) {
  pros::delay(sec);
}

void deployintake() {
  blocker1.set_value(false);
  blocker2.set_value(false);
  thing.set_value(true);
  wait(400);
  thing.set_value(false);
  wait(200);
  blocker1.set_value(true);
  blocker2.set_value(true);
}

void outtake() {
    lFPto.move_voltage(12000);
    rFPto.move_voltage(12000);
}

void intake() {
  lFPto.move_voltage(-12000);
  rFPto.move_voltage(-12000);
}

void stopintake() {
  lFPto.move_voltage(0);
  rFPto.move_voltage(0);
}

void expandWings() {
  wing1.set_value(true);
  wing2.set_value(true);
}

void retractWings() {
  wing1.set_value(false);
  wing2.set_value(false);
}

void extendStick() {
  thing.set_value(true);
}

void retractStick() {
  thing.set_value(false);
}

void shootCata() {
	lFPto.move_voltage(9000);
	rFPto.move_voltage(9000);
  lBPto.move_voltage(9000);
	rBPto.move_voltage(9000);
}

void stopCata() {
	lFPto.move_voltage(0);
	rFPto.move_voltage(0);
  lBPto.move_voltage(0);
	rBPto.move_voltage(0);
}