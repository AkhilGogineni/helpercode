#include "main.h"

using namespace std;

// Chassis constructor
Drive chassis(
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-10, 9, -7}


  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{3, -4, 2}

  // IMU Port

  ,14

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,48.0/36.0

  // Uncomment if using tracking wheels
  /*
  Left Tracking Wheel Ports (negative port will reverse it!)
  ,{1, 2} // 3 wire encoder


  Right Tracking Wheel Ports (negative port will reverse it!)
  ,{-3, -4} // 3 wire encoder
 
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



enum class autonStates { // the possible auton selections
	off,
	RedDescore,
	RedGoalSide,
	BlueDescore,
	BlueGoalSide,
	RedElims,
	BlueElims,
	Skills,
	test
};


autonStates autonSelection = autonStates::off;

static lv_res_t RedLeftBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::RedDescore;
	std::cout << pros::millis() << "RedLeft" << std::endl;
	return LV_RES_OK;
}

static lv_res_t RedRightBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::RedGoalSide;
	std::cout << pros::millis() << "RedRight" << std::endl;
	return LV_RES_OK;
}

static lv_res_t BlueLeftBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::BlueDescore;
	std::cout << pros::millis() << "BlueLeft" << std::endl;
	return LV_RES_OK;
}

static lv_res_t BlueRightBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::BlueGoalSide;
	std::cout << pros::millis() << "BlueRight" << std::endl;
	return LV_RES_OK;
}

static lv_res_t RedSoloWPBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::RedElims;
	std::cout << pros::millis() << "RedSoloWP" << std::endl;
	return LV_RES_OK;
}

static lv_res_t BlueSoloWPBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::BlueElims;
	std::cout << pros::millis() << "BlueSoloWP" << std::endl;
	return LV_RES_OK;
}

static lv_res_t SkillsBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::Skills;
	std::cout << pros::millis() << "Skills" << std::endl;
	return LV_RES_OK;
}

static lv_res_t ResetBtnAction(lv_obj_t *btn) {
	imu.reset();

	leftMotors.tare_position();
	rightMotors.tare_position();

	while (imu.is_calibrating() and pros::millis() < 5000)
	{
		pros::delay(10);
	}
	if (pros::millis() < 5000) std::cout << pros::millis() << ": finished calibrating!" << std::endl;
	return LV_RES_OK;
}

static lv_res_t noAutonBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::off;
	std::cout << pros::millis() << "None" << std::endl;
	return LV_RES_OK;
}



void initialize() {
  	imu.reset();
	
	lv_theme_t *th = lv_theme_alien_init(360, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(th);

	// create a tab view object
	std::cout << pros::millis() << ": creating gui..." << std::endl;
	lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), NULL);

	//button layout
	lv_obj_t *RedTab = lv_tabview_add_tab(tabview, "Red");
	lv_obj_t *BlueTab = lv_tabview_add_tab(tabview, "Blue");
	lv_obj_t *SkillsTab = lv_tabview_add_tab(tabview, "Skills");
	lv_obj_t *OffTab = lv_tabview_add_tab(tabview, "Turn Off");
	

	// Red tab
	lv_obj_t *RedLeftBtn = lv_btn_create(RedTab, NULL);
	lv_obj_t *labelRedLeft = lv_label_create(RedLeftBtn, NULL);

	lv_obj_t *RedRightBtn = lv_btn_create(RedTab, NULL);
	lv_obj_t *labelRedRight = lv_label_create(RedRightBtn, NULL);

	lv_obj_t *RedSoloWPBtn = lv_btn_create(RedTab, NULL);
	lv_obj_t *labelRedSolo = lv_label_create(RedSoloWPBtn, NULL);

	lv_label_set_text(labelRedLeft, "RedDescore");
	lv_btn_set_action(RedLeftBtn, LV_BTN_ACTION_CLICK, RedLeftBtnAction);
	lv_obj_set_size(RedLeftBtn, 150, 50);
	lv_btnm_set_toggle(RedLeftBtn, true, 1);
	lv_obj_set_pos(RedLeftBtn, 0, 0);
	lv_obj_align(RedLeftBtn, NULL, LV_ALIGN_CENTER, -150, -5);

	lv_label_set_text(labelRedRight, "RedGoalSide");
	lv_btn_set_action(RedRightBtn, LV_BTN_ACTION_CLICK, RedRightBtnAction);
	lv_obj_set_size(RedRightBtn, 150, 50);
	lv_btnm_set_toggle(RedRightBtn, true, 1);
	lv_obj_set_pos(RedRightBtn, 0, 0);
	lv_obj_align(RedRightBtn, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_label_set_text(labelRedSolo, "RedElims");
	lv_btn_set_action(RedSoloWPBtn, LV_BTN_ACTION_CLICK, RedSoloWPBtnAction);
	lv_obj_set_size(RedSoloWPBtn, 150, 50);
	lv_btnm_set_toggle(RedSoloWPBtn, true, 1);
	lv_obj_set_pos(RedSoloWPBtn, 0, 0);
	lv_obj_align(RedSoloWPBtn, NULL, LV_ALIGN_CENTER, 150, 12.5);
	

	// Blue tab
	lv_obj_t *BlueLeftBtn = lv_btn_create(BlueTab, NULL);
	lv_obj_t *labelBlueLeft = lv_label_create(BlueLeftBtn, NULL);

	lv_obj_t *BlueRightBtn = lv_btn_create(BlueTab, NULL);
	lv_obj_t *labelBlueRight = lv_label_create(BlueRightBtn, NULL);

	lv_obj_t *BlueSoloWPBtn = lv_btn_create(BlueTab, NULL);
	lv_obj_t *labelBlueSolo = lv_label_create(BlueSoloWPBtn, NULL);

	lv_label_set_text(labelBlueLeft, "BlueDescore");
	lv_btn_set_action(BlueLeftBtn, LV_BTN_ACTION_CLICK, BlueLeftBtnAction);
	lv_obj_set_size(BlueLeftBtn, 150, 50);
	lv_btnm_set_toggle(BlueLeftBtn, true, 1);
	lv_obj_set_pos(BlueLeftBtn, 0, 0);
	lv_obj_align(BlueLeftBtn, NULL, LV_ALIGN_CENTER, -150, -5);

	lv_label_set_text(labelBlueRight, "BlueGoalSide");
	lv_btn_set_action(BlueRightBtn, LV_BTN_ACTION_CLICK, BlueRightBtnAction);
	lv_obj_set_size(BlueRightBtn, 150, 50);
	lv_btnm_set_toggle(BlueRightBtn, true, 1);
	lv_obj_set_pos(BlueRightBtn, 0, 0);
	lv_obj_align(BlueRightBtn, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_label_set_text(labelBlueSolo, "BlueElims");
	lv_btn_set_action(BlueSoloWPBtn, LV_BTN_ACTION_CLICK, BlueSoloWPBtnAction);
	lv_obj_set_size(BlueSoloWPBtn, 150, 50);
	lv_btnm_set_toggle(BlueSoloWPBtn, true, 1);
	lv_obj_set_pos(BlueSoloWPBtn, 0, 0);
	lv_obj_align(BlueSoloWPBtn, NULL, LV_ALIGN_CENTER, 150, 12.5);
	

	//DiagonalDouble tab
	lv_obj_t *OffBtn = lv_btn_create(OffTab, NULL);
	lv_obj_t *Offlabel = lv_label_create(OffBtn, NULL);
	lv_label_set_text(Offlabel, "Turn Off");
	lv_btn_set_action(OffBtn, LV_BTN_ACTION_CLICK, noAutonBtnAction);
	lv_obj_set_size(OffBtn, 450, 50);
	lv_btnm_set_toggle(OffBtn, true, 1);
	lv_obj_set_pos(OffBtn, 0, 100);
	lv_obj_align(OffBtn, NULL, LV_ALIGN_CENTER, 0, 0);


	// skills tab
	lv_obj_t *SkillsBtn = lv_btn_create(SkillsTab, NULL);
	lv_obj_t *skillslabel = lv_label_create(SkillsBtn, NULL);

	lv_label_set_text(skillslabel, "Skills");
	lv_btn_set_action(SkillsBtn, LV_BTN_ACTION_CLICK, SkillsBtnAction);
	lv_obj_set_size(SkillsBtn, 450, 50);
	lv_btnm_set_toggle(SkillsBtn, true, 1);
	lv_obj_set_pos(SkillsBtn, 0, 100);
	lv_obj_align(SkillsBtn, NULL, LV_ALIGN_CENTER, 0, 0);

	//reset btn
	lv_obj_t *ResetBtn = lv_btn_create(tabview, NULL);
	lv_obj_t *ResetLabel = lv_label_create(ResetBtn, NULL);

	lv_label_set_text(ResetLabel, "Reset");
	lv_btn_set_action(ResetBtn, LV_BTN_ACTION_CLICK, ResetBtnAction);
	lv_obj_set_size(ResetBtn, 250, 50);
	lv_btnm_set_toggle(ResetBtn, true, 1);
	lv_obj_set_pos(ResetBtn, 0, 100);
	lv_obj_align(ResetBtn, NULL, LV_ALIGN_CENTER, 0, 50);

	chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.

	// Initialize chassis and auton selector
	default_constants(); // Set the drive to your own constants from autons.cpp!
  	exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

	chassis.initialize();
}

void disabled() {

}

void competition_initialize() {
  // . . .
}



void autonomous() {
	chassis.reset_pid_targets(); // Resets PID targets to 0
	chassis.reset_gyro(); // Reset gyro position to 0
	chassis.reset_drive_sensor(); // Reset drive sensors to 0
	chassis.set_drive_brake(MOTOR_BRAKE_HOLD); 

	if(autonSelection == autonStates::off) {
		autonSelection = autonStates::test;
	}	

	switch(autonSelection) {
		case autonStates::RedDescore:
			RedDescore();
			break;
		case autonStates::RedGoalSide:
			RedGoalSide();
			break;
		case autonStates::BlueDescore:
			BlueDescore();
			break;
		case autonStates::BlueGoalSide:
			BlueGoalSide();
			break;
		case autonStates::RedElims:
			RedElimsLeft();
			break;
		case autonStates::BlueElims:
			BlueElimsLeft();
			break;
		case autonStates::Skills:
			skills();
			break;
		case autonStates::test:
			test();
			break;
		default:
			break;
	}

}



bool frontPtoState = false;
bool backPtoState = false;
bool wings = false;
bool thingState = false;
bool blocker = false;	
bool isShot = false;
double degree = 0;

void opcontrol() {
  // This is preference to what you like to drive on.
  while(true) {
		//chassis code
		if(frontPtoState == false && backPtoState == false) {
            if(abs(controller.get_analog(ANALOG_LEFT_Y)) > 5) {
                //leftMotors.move_voltage(-controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lF.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lFPto.move_voltage(-controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lBPto.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lB.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
            }
            else {
                //leftMotors.move_voltage(0);
				lF.move_voltage(0);
				lFPto.move_voltage(0);
				lBPto.move_voltage(0);
				lB.move_voltage(0);
            }
            if(abs(controller.get_analog(ANALOG_RIGHT_Y)) > 5) {
                //rightMotors.move_voltage(-controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rF.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rFPto.move_voltage(-controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rBPto.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rB.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
            }
            else {
                rF.move_voltage(0);
				rFPto.move_voltage(0);
				rBPto.move_voltage(0);
				rB.move_voltage(0);
            }
			      
				//   leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
			    //   rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

				lF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				lFPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				lBPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				lB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rFPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rBPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }

        if(frontPtoState == false && backPtoState == true) {
            if(abs(controller.get_analog(ANALOG_LEFT_Y)) > 5) {
                //leftMotors.move_voltage(-controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lF.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lFPto.move_voltage(-controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
				lB.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
            }
            else {
                //leftMotors.move_voltage(0);
				lF.move_voltage(0);
				lFPto.move_voltage(0);
				lB.move_voltage(0);
            }
            if(abs(controller.get_analog(ANALOG_RIGHT_Y)) > 5) {
                //rightMotors.move_voltage(-controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rF.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rFPto.move_voltage(-controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
				rB.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
            }
            else {
                rF.move_voltage(0);
				rFPto.move_voltage(0);
				rB.move_voltage(0);
            }
			      
				//   leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
			    //   rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

				lF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				lFPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				lB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rFPto.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
				rB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }
        
        if(frontPtoState == true && backPtoState == false) {
            if(abs(controller.get_analog(ANALOG_LEFT_Y)) > 5) {
                backPtoLeftMotors.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
            }
            else {
                backPtoLeftMotors.move_voltage(0);
            }
            if(abs(controller.get_analog(ANALOG_RIGHT_Y)) > 5) {
                backPtoRightMotors.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
            }
            else {
                backPtoRightMotors.move_voltage(0);
            }
			      backPtoLeftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
			      backPtoRightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        }

        if(frontPtoState == true && backPtoState == true) {
            if(abs(controller.get_analog(ANALOG_LEFT_Y)) > 5) {
                bothPtoLeftMotors.move_voltage(controller.get_analog(ANALOG_LEFT_Y)/127.0*12000);
            }
            else {
                bothPtoLeftMotors.move_voltage(0);
            }
            if(abs(controller.get_analog(ANALOG_RIGHT_Y)) > 5) {
                bothPtoRightMotors.move_voltage(controller.get_analog(ANALOG_RIGHT_Y)/127.0*12000);
            }
            else {
                bothPtoRightMotors.move_voltage(0);
            }
			      bothPtoLeftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
			      bothPtoRightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

        }


		//blocker code
		if(controller.get_digital_new_press(DIGITAL_B)) {
            if(blocker == false){
                blocker1.set_value(false);
                blocker2.set_value(false);
                blocker2ndStage.set_value(false);
                blocker = true;
            }
            else if(blocker == true){
                blocker1.set_value(true);
                blocker2.set_value(true);
                blocker2ndStage.set_value(true);
                blocker = false;
            }
        }

		//intake code
		
		if(frontPtoState && !backPtoState) {
            if(controller.get_digital(DIGITAL_R1)) {
                lFPto.move_voltage(-12000);
                rFPto.move_voltage(-12000);
            } else if(controller.get_digital(DIGITAL_R2)) {
                lFPto.move_voltage(12000);
                rFPto.move_voltage(12000);
            } else {
                lFPto.move_voltage(0);
                rFPto.move_voltage(0);
            }
        } else if(frontPtoState && backPtoState) {
			if(!controller.get_digital(DIGITAL_R2)) {
				if(controller.get_digital(DIGITAL_R1)) {
					lFPto.move_voltage(12000);
					rFPto.move_voltage(12000);
					lBPto.move_voltage(12000);
					rBPto.move_voltage(12000);
				} else {
					lFPto.move_voltage(0);
					rFPto.move_voltage(0);
					lBPto.move_voltage(0);
					rBPto.move_voltage(0);
				}
			}
		} else if(!frontPtoState && backPtoState) {
			if(!controller.get_digital(DIGITAL_R2)) {
				if(controller.get_digital(DIGITAL_R1)) {
					lBPto.move_voltage(-12000);
					rBPto.move_voltage(-12000);
				} else {
					lBPto.move_voltage(0);
					rBPto.move_voltage(0);
				}
			}
		}

		if(!controller.get_digital(DIGITAL_R1)) {
			if(backPtoState) {
				if(controller.get_digital(DIGITAL_R2)) {
					lBPto.move_voltage(9000);
					rBPto.move_voltage(9000);
					if(frontPtoState) {
						lFPto.move_voltage(9000);
						rFPto.move_voltage(9000);
					}
				}
			}
			//std::cout << "rotation sensor angle" << cataTurn.get_angle() << std::endl;
		}

		//front pto code
		if(controller.get_digital_new_press(DIGITAL_L1)) {
            frontPtoState = !frontPtoState;
            std::cout << "front Pto State" << frontPtoState << std::endl;
        } 

        if(frontPtoState) {
            frontPto.set_value(1);
        } else {
            frontPto.set_value(0);
        }

		//back pto code
		if(controller.get_digital_new_press(DIGITAL_L2)) {
            backPtoState = !backPtoState;
            std::cout << "back Pto State" << backPtoState << std::endl;
        } 

        if(backPtoState) {
            backPto.set_value(0);
        } else {
            backPto.set_value(1);
        }

		if(controller.get_digital_new_press(DIGITAL_RIGHT)) {
            if(thingState == false) {
                thing.set_value(true);
                thingState = true;
            
            } else if(thingState == true) {
                thing.set_value(false);
                thingState = false;
            }
        }

		if(controller.get_digital_new_press(DIGITAL_DOWN)) {
            if(wings == false) {
                wing1.set_value(true);
                wing2.set_value(true);
                wings = true;
            
            } else if(wings == true) {
                wing1.set_value(false);
                wing2.set_value(false);
                wings = false;
            }
        }

		if(controller.get_digital_new_press(DIGITAL_Y)) {
            frontPto.set_value(false);
			backPto.set_value(true);
        }


    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
	}
}
