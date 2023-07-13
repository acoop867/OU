#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor l1 = motor(PORT7, ratio6_1, false);
motor l2 = motor(PORT5, ratio6_1, true);
motor l3 = motor(PORT3, ratio6_1, true);
motor r1 = motor(PORT10, ratio6_1, true);
motor r2 = motor(PORT9, ratio6_1, false);
motor r3 = motor(PORT8, ratio6_1, false);
inertial Inertial4 = inertial(PORT4);
rotation lr = rotation(PORT11, false);
rotation rr = rotation(PORT20, true);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}