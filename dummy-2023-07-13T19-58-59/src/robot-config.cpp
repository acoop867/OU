#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
 
// VEXcode device constructors
motor l1 = motor(PORT5, ratio6_1, false);
motor l2 = motor(PORT20, ratio6_1, true);
motor l3 = motor(PORT17, ratio6_1, true);
motor r1 = motor(PORT3, ratio6_1, true);
motor r2 = motor(PORT12, ratio6_1, false);
motor r3 = motor(PORT14, ratio6_1, false);
inertial Inertial4 = inertial(PORT10);
rotation lr = rotation(PORT11, false);
rotation rr = rotation(PORT21, true);
controller Controller1 = controller(primary);
motor Intake = motor(PORT4, ratio18_1, false);
motor cata = motor(PORT8, ratio18_1, false);
limit LimitSwitchA = limit(Brain.ThreeWirePort.A);
motor arm = motor(PORT19, ratio18_1, true);
digital_out wingR = digital_out(Brain.ThreeWirePort.G);
digital_out wingL = digital_out(Brain.ThreeWirePort.H);
line lines = line(Brain.ThreeWirePort.E);

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