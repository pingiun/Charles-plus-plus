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

#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>

#include "cli_control.h"

// Variabelen
const int WereldBreedte = 50;
const int WereldHoogte	= 30;

// Functies
void step();
void turn_left();
void turn_right();
bool in_front_of_wall();
bool north();
bool on_ball();
void get_ball();
void put_ball();

void steps(int steps);
void place_rectangle(int x, int y, int width, int height);
void place_walls(int x, int y, int n, bool horizontal);

void reset();

void create_ball(int xcor, int ycor);
void _put_wall(int xcor, int ycor);
void _position_robot(int xcor, int ycor);
void _draw();
void set_sleep(int);

void make_string_with_balls();
void make_chaos_with_balls();

class Robot {
  cli_control* cli;
 public:
  Robot(cli_control* c);
  void set_sleep(int);
  void universal_sleep();
  void step();
  void turn_left();
  void turn_right();
  bool in_front_of_wall();
  bool north();
  bool on_ball();
  void get_ball();

  void place_rectangle(int x, int y, int width, int height);
  void place_walls(int x, int y, int n, bool horizontal);

  void reset();

  void _put_ball(int xcor, int ycor);
  void _put_wall(int xcor, int ycor);
  void _position_robot(int xcor, int ycor);
  void _draw();
};

#endif // ROBOT_H
