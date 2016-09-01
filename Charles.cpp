// Charles++ a better version of Charles
// Copyright (C) 2016 Jelle Besseling
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <string.h>

#include "Robot.h"
#include "cli_control.h"

using namespace std;

// =========================================================================

// Here are the examples that have been explained during the lecture
void take_3_steps ()
{
    step () ;
    step () ;
    step () ;
}

void swap_ball ()
{
    if (on_ball ())
        get_ball () ;
    else
	      put_ball () ;
    step () ;
}

// put_a_ball_somewhere adds a single ball to Charles' world on a random location
void put_a_ball_somewhere ()
{
    int lane   = 1 + rand () % (WereldHoogte  - 2) ;
    int street = 1 + rand () % (WereldBreedte - 2) ;
    create_ball (street, lane) ;
}

// make_church creates a Church-like shape of walls
void make_church ()
{
    place_rectangle (10,10,20,8) ;
    place_rectangle (10,18, 4,4) ;
    place_walls (12,22,4,false) ;
    place_walls (11,25,2,true) ;
}

// make_block creates an arbitrary block inside Charles' world and places a ball
// on the 'north' most lane at the 'west' most street corner.
void make_block ()
{
    const int left   = rand () % (WereldBreedte / 3) + 5;
    const int bottom = rand () % (WereldHoogte  / 4) + 5;
    const int width  = rand () % (WereldBreedte / 2) + 5;
    const int height = rand () % (WereldHoogte  / 2) + 2;
    place_rectangle (left,bottom,width,height) ;
    create_ball (left, 0) ;
}
// turn_north makes Charles look north
void turn_north ()
{
    while (!north())
        turn_left();
}

void turn_around ()
{
    turn_left() ;
    turn_left() ;
}
// walk_to_wall makes Charles walk ahead and stop immediately before the wall
void walk_to_wall ()
{
    while (!in_front_of_wall())
        step () ;
}

// go_to_north_west_corner makes Charles move to north-west corner and look to the east
// it is assumed that that there are only the exterior walls
void go_to_north_west_corner ()
{
    turn_north() ;
    walk_to_wall() ;
    turn_left() ;
    walk_to_wall() ;
    turn_around() ;
}

// sweep_lane makes Charles walk ahead until it is on top of a ball or immediately before a wall
void sweep_lane ()
{
    while (!on_ball() && !in_front_of_wall())
        step () ;
}

// go_down_east_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing east and is not on the southernmost lane
void go_down_east_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_right() ;
        step() ;
        turn_right() ;
    }
}

// go_down_west_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing west and is not on the southernmost lane
void go_down_west_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_left () ;
        step () ;
        turn_left () ;
    }
}

// sweep_lanes makes Charles move to the east and find the ball, followed by
// going on lane south and moving to the west to find the ball.
// Assumptions: Charles is standing at the north-west corner and is looking east, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball
void sweep_lanes ()
{
    while (!on_ball())
    {
        sweep_lane () ;
        go_down_east_if_not_on_ball () ;
        sweep_lane () ;
        go_down_west_if_not_on_ball () ;
    }
}

// This example has been discussed during the lecture
// The effect of this function is that Charles will search for a ball in its universe.
// Assumptions: Charles is standing on its base position, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball.
void find_ball ()
{
    sweep_lanes () ;
}

// here starts the part with code to be completed by the students

// Name / student number / study student 1 :
// Name / student number / study student 2 :

// give one or more comment lines about what will happen in this function
void clean_string_with_balls ()
{
	make_string_with_balls () ;
	// give your own code completion
}

// give one or more comment lines about what will happen in this function
void clean_chaos_with_balls ()
{
	make_chaos_with_balls () ;
	// give your own code completion
}

// this is the initial set-up for the tracing Charles assignment
void tracing_Charles ()
{
    reset () ;
    create_ball (WereldBreedte - 5, WereldHoogte - 3) ;
    steps (WereldBreedte - 5) ;
}

// give one or more comment lines about what will happen in this function
void around_the_block ()
{
    make_block () ;
    // give your own code completion
}

// Charles searches for the ball and remains there
void search_the_ball ()
{
	put_a_ball_somewhere () ;
	find_ball () ;
}

// For testing purposes, you can define your own function here:
void test ()
{
    // enter your Charles code here
}

// end of part with code to be completed by students
// =========================================================================

int main(int argc, char* argv[]) {
  int sleeptime = atoi(argv[1]);
  if (sleeptime != 0) {
    cout << "Sleep time: " << sleeptime << endl;
    set_sleep(sleeptime);
  } else {
    cout << "Please provide an integer for the sleep time." << endl;
    return 1;
  }
  cout << "Welcome by Charles++, because we don't have a GUI interface, you can now choose a function to run." << endl;
  cout << "1. Assignment 1: clean_string_with_balls ()" << endl;
  cout << "2. Assignment 2: clean_chaos_with_balls ()" << endl;
  cout << "3. Example search the ball: search_the_ball ()" << endl;
  cout << "4. Bonus: around_the_block ()" << endl;
  cout << "5. Test function: test ()" << endl;
  while (true) {
    cout << "Choose one of the options 1-5" << endl;
    int option;
    cin >> option;
    switch (option){
    case 1:
      _draw();
      clean_string_with_balls();
      return 0;
    case 2:
      _draw();
      clean_chaos_with_balls();
      return 0;
    case 3:
      _draw();
      search_the_ball();
      return 0;
    case 4:
      _draw();
      around_the_block();
      return 0;
    case 5:
      _draw();
      test();
      return 0;
    }
  }
  return 0;
}
