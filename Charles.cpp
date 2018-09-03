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
#include <ctime>

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
    const int lane   = 2 + rand () % (WereldHoogte / 5) ;
    const int street = 2 + rand () % (WereldBreedte / 5) ;
    const int width  = 3 + rand () % (WereldBreedte / 2) ;
    const int height = 2 + rand () % (WereldHoogte / 3) ;
    place_rectangle (street,lane,width,height) ;
    place_rectangle (street + 2,lane + height, 2 + width / 3, 2 + height / 3) ;
    place_walls (street + 3 + width / 6,lane + height + height / 3 + 2,4,false) ;
    place_walls (street + 2 + width / 6,lane + height + height / 3 + 5,2,true) ;
    create_ball (street, WereldHoogte - 2) ;
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
    create_ball (left, WereldHoogte-2) ;
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

// here starts the part with code to be completed by the students for assignment 1

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

// here starts the part with code to be completed by the students for assignment 2

// Name / student number / study student 1 :
// Name / student number / study student 2 :
// ==========================================================================

// give one or more comment lines about what will happen in this function
void follow_path ()
{
    // give your own code completion
}

// give one or more comment lines about what will happen in this function
void hansl_and_gretl ()
{
	make_path_with_balls() ;
	follow_path () ;
}

// give one or more comment lines about what will happen in this function
// note that you are allowed to add formal parameters to fill_cave_with_balls if that is necessary for your solution
void fill_cave_with_balls ()
{
    // give your own code completion
}

// give one or more comment lines about what will happen in this function
void cave ()
{
	// if necessary for your solution, you are allowed to give actual parameters to fill_cave_with_balls
	fill_cave_with_balls () ;
	fill_cave_with_balls () ;
}

// give one or more comment lines about what will happen in this function
void start_cave ()
{
    make_cave () ;
    cave () ;
}

// give one or more comment lines about what will happen in this function
void rondje_om_de_kerk ()
{
    make_church () ;
    // give your own code completion
}

// For testing purposes, you can define your own function here:
void test ()
{
    // enter your Charles code here
}

// end of part with code to be completed by students
// =========================================================================

int main(int argc, char* argv[]) {
    if (argc == 2){
        int sleeptime = atoi(argv[1]);
        if (sleeptime != 0) {
            cout << "Sleep time: " << sleeptime << endl;
            set_sleep(sleeptime);
        } else {
            cout << "Please provide an integer for the sleep time." << endl;
            return 1;
        }
    } else {
        set_sleep(1000);
    }

    srand((int) time(NULL));

    cout << "Welcome by Charles++, because we don't have a GUI interface, you can now choose a function to run." << endl;
    cout << "=============" << endl;
    cout << "Assignment 1:" << endl;
    cout << "1. Assignment 1.1: clean_string_with_balls ()" << endl;
    cout << "2. Assignment 1.2: clean_chaos_with_balls ()" << endl;
    cout << "3. Example search the ball: search_the_ball ()" << endl;
    cout << "4. Bonus: around_the_block ()" << endl;
    cout << "=============" << endl;
    cout << "Assignment 2:" << endl;
    cout << "5. Assignment 2.1: follow_path ()" << endl;
    cout << "6. Assignment 2.2: fill_cave_with_balls ()" << endl;
    cout << "7. Bonus: rondje_om_de_kerk ()" << endl;
    cout << "=============" << endl;
    cout << "8. Test function: test ()" << endl;
    
    while (true) {
        cout << "Choose one of the options 1-5" << endl;
        int option;
        cin >> option;
        
        switch (option){
        case 1:
            clean_string_with_balls();
            return 0;
        case 2:
            clean_chaos_with_balls();
            return 0;
        case 3:
            search_the_ball();
            return 0;
        case 4:
            around_the_block();
            return 0;
        case 5:
            hansl_and_gretl();
            return 0;
        case 6:
            start_cave();
            return 0;
        case 7:
            rondje_om_de_kerk();
            return 0;
        case 8:
            test();
            return 0;
        default:
            cout << "Invalid option, try again" << endl;
        }
    }
    return 0;
}
