#ifndef CONFIG_H
#define CONFIG_H

extern pros::Controller master;
extern pros::Motor leftfront  ;
extern pros::Motor leftback   ;
extern pros::Motor rightfront ;
extern pros::Motor rightback  ;
extern pros::Motor lift   ;
extern pros::Motor claw  ;
extern int automode;
enum redblue {red=1, blue=-1};
enum frontback {front=1, back=-1};
extern redblue iside;
extern frontback isfront;
#endif
