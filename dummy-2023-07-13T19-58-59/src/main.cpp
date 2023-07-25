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
// l1                   motor         10              
// l2                   motor         16              
// l3                   motor         3               
// r1                   motor         13              
// r2                   motor         18              
// r3                   motor         6               
// Inertial4            inertial      4               
// lr                   rotation      11              
// rr                   rotation      20              
// Controller1          controller                    
// Intake               motor         1               
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
     kp=.35;
     ki=0;
     kd=0;
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
  while(fabs(deg-Inertial4.rotation())>3&&!testr()&&!testl()) {
  sl(pid(deg,Inertial4.rotation(degrees),2));
  sr(-pid(deg,Inertial4.rotation(degrees),2));
  }
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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  thread t(thr);
  Inertial4.calibrate();
  wait(4,sec);
  

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
