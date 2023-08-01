/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Thu Jul 13 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// l1                   motor         5               
// l2                   motor         20              
// l3                   motor         17              
// r1                   motor         3               
// r2                   motor         12              
// r3                   motor         14              
// Inertial4            inertial      18              
// lr                   rotation      11              
// rr                   rotation      21              
// Controller1          controller                    
// Intake               motor         4               
// cata                 motor         8               
// LimitSwitchA         limit         A               
// Arm                  motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


int i = 0;
int prev=0;
void reset() {
  i=0;
  prev=0;
}

bool testl(){
  int t =0;
  float l=lr.position(degrees);
  for(int i=0; i<3;i++) {
    if(fabs(lr.position(degrees)-l)<3) {
      t++;
    }
    else return false;
  }
  if(t>3) return true;
  else return false;
}
bool testr(){
  int t =0;
  float l=rr.position(degrees);
  for(int i=0; i<3;i++) {
    if(fabs(rr.position(degrees)-l)<3) {
      t++;
    }
    else return false;
  }
  if(t>3) return true;
  else return false;
}

int pid(int dist,int sense,int s) {
  double kp,ki,kd,max;
  if (s==1) {
     kp=.03;
     ki=0.0;
     kd=0.1;
     max=50;
  }
  else{
     kp=.4;
     ki=0;
     kd=.05;
     max=60;
  }
  int p=dist-sense;
  if(p<50){
  i +=p;
  }
  else{
    i=0;
  }
  int d=p-prev;
  prev=p;
  if(p*kp+i*ki+d*kd>max) return max;
  else return p*kp+i*ki+d*kd;
}


void sl(int speed) {
  l1.spin(forward,speed,pct);
  l2.spin(forward,speed,pct);
  l3.spin(forward,speed,pct);
}
void sr(int speed) {
  r1.spin(forward,speed,pct);
  r2.spin(forward,speed,pct);
  r3.spin(forward,speed,pct);
}

void arc(int dist, int diff) {
  lr.resetPosition();
  rr.resetPosition();
  
  while(fabs((lr.position(degrees)+rr.position(degrees))/2-dist)>50||fabs(Inertial4.rotation(degrees)+diff)>4) {
  sl(pid(dist,lr.position(degrees),1)-pid(diff,Inertial4.rotation(degrees),2));
  sr(pid(dist,rr.position(degrees),1)+pid(diff,Inertial4.rotation(degrees),2));
  wait(10,msec);
  }
  sl(0);
  sr(0);
}

int thr() {
  while(true) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(lr.position(degrees));
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print(rr.position(degrees));
  Controller1.Screen.setCursor(3,1);
  Controller1.Screen.print(Inertial4.rotation(degrees));
  wait(25,msec);
  }return 0;
}

void swingl(float tim) {
  sl(60);
  wait(tim,sec);
  sl(0);
}

void swingrb(float tim) {
  
  sl(-60);
  sr(-10);
  wait(tim,sec);
  sl(0);
  sr(0);
}

void turnm(int deg) {
  while(fabs(deg-Inertial4.rotation())>1.5&&!testr()&&!testl()) {
  sl(pid(deg,Inertial4.rotation(degrees),2));
  sr(-pid(deg,Inertial4.rotation(degrees),2));
  }
  sl(0);
  sr(0);
}
void df(float tim,bool s) {int speed=60;
  if(s) {
    speed=30;
  }
  sl(speed);
  sr(speed);
  wait(tim,sec);
  sl(0);
  sr(0);
}
void df(float tim) {
  sl(60);
  sr(60);
  wait(tim,sec);
  sl(0);
  sr(0);
}
void db(float tim) {
  sl(-60);
  sr(-60);
  wait(tim,sec);
  sl(0);
  sr(0);
}

void intake(bool s,bool dir) {
  if(s&&dir) {
    Intake.spin(forward,100,pct);
  }
  else if(s) {
    Intake.spin(reverse,100,pct);
  }
  else{
    Intake.stop();
  }
}

void cat() {
  if(!LimitSwitchA.pressing()){
      cata.spin(fwd,100,pct);
      while(!LimitSwitchA.pressing()) {
        wait(1,msec);
      }
      cata.stop();
  }
}
void cataspin() {
  while(true){
    if(LimitSwitchA.pressing() and !Controller1.ButtonL2.pressing()){
      cata.stop(hold);
    }else{
      cata.spin(fwd,100,pct);
    }
  wait(1,msec);
  }
}

void armFreeSpin(bool direction){//this does not hold arm so that the motor does not get damedged
  arm.setBrake(coast);
  if (direction == true){
    arm.spin(fwd,100,pct);
  }else{
    arm.spin(reverse,100,pct);
  }
  wait(0.5,seconds);
  arm.stop(coast);
}

void armtime(bool direction,float time){//this does not hold arm so that the motor does not get damedged
  if (direction == true){
    arm.spin(fwd,100,pct);
  }else{
    arm.spin(reverse,100,pct);
  }
  wait(time,seconds);
  arm.stop(hold);
}

competition Comp;


int choice=0;
void auton() {
  
  
  
  if(choice == 0) { //defense
    df(.5);
    turnm(-10);
    db(.4);
    turnm(40);
    df(.8);
    db(.3);
    turnm(95);
    df(.5);
    db(.2);
    turnm(240);
    df(1);
    db(.2);
    turnm(150);
    df(.4);
    turnm(100);
    df(.5);
    db(.01);
  }
  if(choice ==1) { //offense
    db(.4);
    cat();
    cata.setBrake(coast);
    wait(.2,seconds);
    cata.setBrake(hold);
    wait(.2,seconds);
    df(.27,true);
    turnm(112);
    intake(true,true);
    df(2,true);
    
    turnm(0);
    intake(false,true);
    db(.61);
    turnm(90);
    df(.2);
    

    
    wingL.set(1);

    db(.4);
    
    armtime(false, .5);
    db(.7);

    df(.3);
    turnm(-90);
    intake(true,false);
    df(.3);
  }
  if(choice == 3) { //offense bad

    armFreeSpin(true);
    arm.setPosition(0, degrees);
    armtime(false, .22);
    wait(.2,seconds);
    db(.05);
    turnm(-77);
    df(.15);
    
    armFreeSpin(true);
    
     db(.2);
     df(.2);
     armtime(false,.22);
     wait(.4,seconds);

     turnm(-90);
     db(.4);
     turnm(0);
     df(.52);
     turnm(-90);
     intake(true,true);
     df(.4);
     intake(false,true);
     armFreeSpin(true);
     db(.2);
     turnm(0);
     
     df(.2);
     wait(.2,seconds);

     turnm(55);
     armFreeSpin(false);
     intake(true,false);
     df(.5);
     
    
    

  }
  if(choice == 2) { //skills
    cata.spin(forward, 100, pct);
    wait(35, seconds);
    cata.stop();
    df(.5);
    turnm(35);
    wingR.set(true);
    wingL.set(true);

    df(1);
  }



}


void driver() {
  bool ArmButtonP= true;//if both buttons are pressed for toggle
  int ArmState=1;// state of arm
  int wstate=0;


  while (true) {
    

    arm.setBrake(hold);
    sl(Controller1.Axis3.position()+Controller1.Axis1.position()/1.5);
    sr(Controller1.Axis3.position()-Controller1.Axis1.position()/1.5);

    if(Controller1.ButtonDown.pressing()){//turns on the cata auto loop. Fixes the accidental release
      thread t(cataspin);
    }

    if(Controller1.ButtonR2.pressing()) {
      while(Controller1.ButtonR2.pressing()) {
        wait(10,msec);
      }
      wstate++;
      if(wstate>1) {
        wstate=0;
      }
      wingR.set(wstate);
      wingL.set(wstate);
    }
    
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(reverse,100,pct);
    }else if (Controller1.ButtonL1.pressing()) {
      Intake.spin(forward,100,pct);
    }else{
      Intake.stop();
    }
    if (Controller1.ButtonR1.pressing() and Controller1.ButtonL1.pressing() and ArmButtonP){
      if (ArmState !=1){
        ArmState = 1;
        armFreeSpin(false);
      }else{
        ArmState = 2;
        armFreeSpin(true);
      }
      ArmButtonP= false;
    }else if(!Controller1.ButtonR1.pressing() or !Controller1.ButtonL1.pressing()){
      ArmButtonP= true;
    }


    //wait(10,msec);
  }
}

void pre() {
  vexcodeInit();
  Inertial4.calibrate();
  choice = 1;
  while(!Comp.isEnabled()) {
    if(Brain.Screen.pressing()) {
      while(Brain.Screen.pressing()) {
        wait(10,msec);
      }
      choice++;
      if(choice>2) {
        choice =0;
      }
    }
    
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    if(choice == 0) {
      Brain.Screen.print("Defense");
    }
    if(choice == 1) {
      Brain.Screen.print("Offense");
    }
    if(choice == 2) {
      Brain.Screen.print("Skills");
    }


  }
  
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Comp.autonomous(auton);
  Comp.drivercontrol(driver);

  pre();

  
  
  while(1){
    wait(100,msec);
  }

}