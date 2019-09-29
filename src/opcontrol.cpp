#include "main.h"
#include "config.hpp"
#include <iomanip>
//#include "userFn.hpp"
/*
cd (change directory)
cd .. (go up one level)
prosv5 make clean (clean everything)
prosv5 build-compile-commands (compile the code)
prosv5 upload --slot 5 (upload the program to V5 slot 5)
prosv5 v5 rm-all
prosv5 v5 rm-file slot_4.bin --erase-all
*/

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  //pros::lcd::initialize();
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  char mytext[100];

  	/*Create a screen*/
  	lv_obj_t * scr = lv_obj_create(NULL, NULL);
  	lv_scr_load(scr);                                   /*Load the screen*/

  	lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
  	lv_label_set_text(title, "Debug");
  	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 2);  /*Align to the top*/

  	/*Create anew style*/
  	/*
  	static lv_style_t style_txt;
  	lv_style_copy(&style_txt, &lv_style_plain);
  	style_txt.text.font = &lv_font_dejavu_20;
  	style_txt.text.letter_space = 2;
  	style_txt.text.line_space = 1;
  	style_txt.text.color = LV_COLOR_HEX(0x606060);
  	*/

  	/*Create a new label*/
  	lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
  	//lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
  	lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  	lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
  	lv_label_set_align(txt, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/
  	lv_label_set_text(txt, NULL);
  	lv_obj_set_width(txt, 500);                           /*Set a width*/
  	lv_obj_align(txt, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);      /*Align to center*/

	while(true){


		lv_label_set_text(txt, mytext);

		int updown = master.get_analog (ANALOG_LEFT_Y);
    int side   = master.get_analog(ANALOG_LEFT_X);
		int turn   = master.get_analog (ANALOG_RIGHT_X);
		//pros::lcd::print(0, "limitswitch: %d, life position: %8.1f\n", limitswitch.get_value(), lift.get_position());
		//pros::lcd::print(1, "potentiameter: %d\n", potentiameter.get_value());
		//pros::lcd::print(2, "left: %8.1f, right %8.1f\n", leftfront.get_position(), rightfront.get_position());
		//pros::lcd::print(3, "catapult: %8.1f, reset %d\n", catapult.get_position(), limitswitchball.get_value());
		//pros::lcd::print(4, "claw: %8.1f\n", claw.get_position());

    // press DIGITAL_DOWN to reset zero
		if (master.get_digital(DIGITAL_DOWN))  {
			leftfront.tare_position ( );
			rightfront.tare_position ( );
		}

	  	// chasis
			leftfront.move  (updown + side + turn);
			leftback.move   (updown - side + turn);
			rightfront.move (updown - side - turn);
			rightback.move  (updown + side - turn);

      if (master.get_digital(DIGITAL_L1))  {
  			lift.move_velocity(100);
  		}
      else if (master.get_digital(DIGITAL_L2))  {
      	lift.move_velocity(-100);
    	}
      else {
    		lift.move_velocity(0);
    	}

      //claw
      if (master.get_digital(DIGITAL_R1))  {
    		claw1.move_velocity(150);
        claw2.move_velocity(150);
      }
      else if (master.get_digital(DIGITAL_R2))  {
        claw1.move_velocity(-150);
        claw2.move_velocity(-150);
      }
      else {
        claw1.move_velocity(0);
        claw2.move_velocity(0);
      }

      //stacker
      if (master.get_digital(DIGITAL_X))  {
        stacker.move_velocity(50);

      }
      else if (master.get_digital(DIGITAL_A))  {
        stacker.move_velocity(-50);
      }
      else {
        stacker.move_velocity(0);
    	}
    }
}
