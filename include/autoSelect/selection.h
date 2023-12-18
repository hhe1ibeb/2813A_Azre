#pragma once

#include <string>

//selector configuration
#define HUE 360
#define DEFAULT 2
#define AUTONS "Near", "Far", "Do Nothing"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
