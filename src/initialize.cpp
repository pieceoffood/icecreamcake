#include "main.h"
#include "config.hpp"
#include <string>


pros::Controller master  (pros::E_CONTROLLER_MASTER);
pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftback   (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightback  (9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift       (5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor claw1       (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor claw2       (7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor stacker       (8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//pros::ADIDigitalIn limitswitch  (1);
//pros::ADIAnalogIn potentiameter (2);
//pros::ADIGyro gyro (3);
//pros::ADIDigitalIn limitswitchball(4);
int automode = 0;
// 1 red front
// 2 blue front
// 3 red back
// 4 blue back
// 5 skill program 1
// 6 skill program 2

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
    printf("Button: %s released\n", txt);
    if (strcmp(txt, "redfront")==0)  automode=1;
    else if (strcmp(txt, "bluefront")==0) automode=2;
    else if (strcmp(txt, "redback")==0)   automode=3;
    else if (strcmp(txt, "blueback")==0) automode=4;
    else if (strcmp(txt, "redfront nopark")==0) automode=5;
    else if (strcmp(txt, "bluefront nopark")==0)   automode=6;
    else if (strcmp(txt, "skill 1")==0)   automode=7;
    else if (strcmp(txt, "skill 2")==0)   automode=8;
    else if (strcmp(txt, "no auto")==0)   automode=9;
    else automode=10;
    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  lift.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  //claw.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  //leftback.set_brake_mode      (pros::E_MOTOR_BRAKE_COAST);
  //rightback.set_brake_mode     (pros::E_MOTOR_BRAKE_COAST);



	/*Create a title label*/
lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(label, "auto selection");
lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 5);

/*Create a button descriptor string array*/
static const char * btnm_map[] = {"redfront", "bluefront", "redback", "blueback", "\n",
													 "skill 1",  "skill 2", "no auto", ""
													};

/*Create a default button matrix*/
static lv_style_t style_bg;
lv_style_copy(&style_bg, &lv_style_plain);
//style_bg.body.main_color = LV_COLOR_SILVER;
//style_bg.body.grad_color = LV_COLOR_SILVER;
style_bg.body.padding.hor = 0;
style_bg.body.padding.ver = 0;
style_bg.body.padding.inner = 0;

lv_obj_t * btnm1 = lv_btnm_create(lv_scr_act(), NULL);
lv_btnm_set_map(btnm1, btnm_map);
lv_btnm_set_action(btnm1, btnm_action);
lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BG, &style_bg);
lv_obj_set_size(btnm1, LV_HOR_RES, LV_VER_RES / 2);
lv_btnm_set_toggle(btnm1, true, 6);

/*Create a new style for the button matrix back ground*/
/*Create 2 button styles*/

static lv_style_t style_btn_rel;
static lv_style_t style_btn_pr;
lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
style_btn_rel.body.grad_color = LV_COLOR_BLACK;
style_btn_rel.body.border.color = LV_COLOR_SILVER;
style_btn_rel.body.border.width = 1;
style_btn_rel.body.border.opa = LV_OPA_50;
style_btn_rel.body.radius = 0;

lv_style_copy(&style_btn_pr, &style_btn_rel);
style_btn_pr.body.main_color = LV_COLOR_MAKE(0x55, 0x96, 0xd8);
style_btn_pr.body.grad_color = LV_COLOR_MAKE(0x37, 0x62, 0x90);
style_btn_pr.text.color = LV_COLOR_MAKE(0xbb, 0xd5, 0xf1);
lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_PR, &style_btn_pr);


  master.print(0, 0, "automode: %d", automode);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
