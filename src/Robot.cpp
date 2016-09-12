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
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef __unix__
#include <unistd.h>
#endif // __unix__

#include "Robot.h"
#include "cli_control.h"

using namespace std;

Robot::Robot(cli_control* c) {
  cli = c;
}

void Robot::set_sleep(int mssleep) {
  cli->milli = mssleep;
}

void Robot::universal_sleep() {
#ifdef _WIN32
  Sleep(cli->milli);
  return;
#endif
#ifdef __unix__
  usleep(cli->milli * 1000);
  return;
#endif
  return;
}

void Robot::_put_ball(int xcor, int  ycor) {
  cli->balls[xcor][ycor] = true;
}

void Robot::get_ball() {
  cli->balls[cli->robotx][cli->roboty] = false;
}

void Robot::_put_wall(int xcor, int ycor) {
  cli->walls[xcor][ycor] = true;
}

void Robot::_position_robot(int xcor, int ycor) {
  cli->robotx = xcor;
  cli->roboty = ycor;
}

void Robot::step() {
  switch (cli->orientation) {
  case Orientation::North:
    cli->roboty--;
    break;
  case Orientation::East:
    cli->robotx++;
    break;
  case Orientation::South:
    cli->roboty++;
    break;
  case Orientation::West:
    cli->robotx--;
    break;
  }
  ::_draw();
}

void Robot::turn_left() {
  switch (cli->orientation) {
  case Orientation::North:
    cli->orientation = Orientation::West;
    break;
  case Orientation::East:
    cli->orientation = Orientation::North;
    break;
  case Orientation::South:
    cli->orientation = Orientation::East;
    break;
  case Orientation::West:
    cli->orientation = Orientation::South;
    break;
  }
  ::_draw();
}

void Robot::turn_right() {
  switch (cli->orientation) {
  case Orientation::North:
    cli->orientation = Orientation::East;
    break;
  case Orientation::East:
    cli->orientation = Orientation::South;
    break;
  case Orientation::South:
    cli->orientation = Orientation::West;
    break;
  case Orientation::West:
    cli->orientation = Orientation::North;
    break;
  }
  ::_draw();
}

bool Robot::in_front_of_wall() {
  switch (cli->orientation) {
  case Orientation::North:
    return cli->walls[cli->robotx][cli->roboty-1] || cli->roboty - 1 < 0;
  case Orientation::East:
    return cli->walls[cli->robotx+1][cli->roboty] || cli->robotx + 1 > 47;
  case Orientation::South:
    return cli->walls[cli->robotx][cli->roboty+1] || cli->roboty + 1 > 27;
  case Orientation::West:
    return cli->walls[cli->robotx-1][cli->roboty] || cli->robotx - 1 < 0;
  }
  return false;
}

bool Robot::north() {
  return cli->orientation == Orientation::North;
}

bool Robot::on_ball() {
  return cli->balls[cli->robotx][cli->roboty];
}

void Robot::place_rectangle(int x, int y, int width, int height) {
  y = (WereldHoogte - 3) - (y - 1) - height;
  x = x - 1;
  for (int i = x; i < x + width; i++) {
    cli->walls[i][y] = true;
    cli->walls[i][y+height] = true;
  };

  for (int i = y; i <= y + height; i++) {
    cli->walls[x][i] = true;
    cli->walls[x+width][i] = true;
  };
  ::_draw();
}

void Robot::place_walls(int x, int y, int n, bool horizontal) {
  x = x - 1;
  if (horizontal) {
    y = (WereldHoogte - 3) - (y - 1);
    for (int i = x ; i <= x + n ; i++) {
      cli->walls[i][y] = true;
    }
  } else {
    y = (WereldHoogte - 3) - (y - 1) - n;
    for (int i = y; i < y + n ; i++) {
      cli->walls[x][i] = true;
    }
  }
  ::_draw();
}

void Robot::make_path_with_balls(){
	for (int ix = 1; ix < WereldBreedte-8; ix++)
        cli->balls[ix - 1][(WereldHoogte - 3) - (WereldHoogte-2 - 1)]  = true;
	for (int iy = WereldHoogte-2; iy > WereldHoogte/2; iy--)
        cli->balls[WereldBreedte-9][(WereldHoogte - 3) - (iy - 1)] = true;
	for (int ix = WereldBreedte-8; ix >= 1; ix--)
        cli->balls[ix - 1][(WereldHoogte - 3) - (WereldHoogte/2 - 1)]  = true;
	for (int iy = WereldHoogte/2; iy >= 4; iy--)
        cli->balls[0][(WereldHoogte - 3) - (iy - 1)] = true;
	for (int ix = 1; ix <= WereldBreedte/3; ix++)
        cli->balls[ix - 1][(WereldHoogte - 3) - (4 - 1)]               = true;
	for (int iy = 4; iy <= WereldHoogte * 2 / 3; iy++)
        cli->balls[WereldBreedte/3 - 1][(WereldHoogte - 3) - (iy - 1)] = true;
    ::_draw();
}

void Robot::make_cave() {
    const int marge       = WereldHoogte / 3 ;
    const int max_breedte = WereldBreedte / 10 ;

    for (int ix = 2; ix <= WereldBreedte-3; )
    {
        const int breedte = rand() % (min (max_breedte, WereldBreedte - ix - 2)) + 1 ;
        const int dy = rand() % marge + 2 ;
        int y ;
        y = dy ;
        for (int i=1; i <= breedte; i++)
        {
            cli->walls[ix - 1][(WereldHoogte - 3) - (y - 1)] = true ;
            ix++ ;
        }
    }
    for (int ix = 2; ix <= WereldBreedte-3; )
    {
        const int breedte = rand() % (min (max_breedte, WereldBreedte - ix - 2)) + 1 ;
        const int dy = rand() % marge + 2 ;
        int y ;
        y = WereldHoogte - dy - 1 ;
        for (int i=1; i <= breedte; i++)
        {
            cli->walls[ix - 1][(WereldHoogte - 3) - (y - 1)] = true ;
            ix++ ;
        }
    }
    ::_draw();
}

static cli_control c;
void steps(int steps) {
  for (int i = 0; i < steps; i++) {
    Robot(&c).step();
  }
}

void place_rectangle(int x, int y, int width, int height) {
  Robot(&c).place_rectangle(x, y, width, height);
}

void place_walls(int x, int y, int n, bool horizontal) {
  Robot(&c).place_walls(x, y, n, horizontal);
}

void Robot::reset() {
  cli->reset();
}

void step() {
  Robot(&c).step();
}
void turn_left() {
  Robot(&c).turn_left();
}
void turn_right() {
  Robot(&c).turn_right();
}
bool in_front_of_wall() {
  return Robot(&c).in_front_of_wall();
}
bool north() {
  return Robot(&c).north();
}

bool on_ball() {
  return Robot(&c).on_ball();
}

void put_ball() {
  if (c.balls[c.robotx][c.roboty]) {
    throw runtime_error("There's already a ball at that location!");
  } else {
    Robot(&c)._put_ball(c.robotx, c.roboty);
  }
}

void get_ball() {
  if (!c.balls[c.robotx][c.roboty]) {
    throw runtime_error("There's no ball at that location!");
  } else {
    Robot(&c).get_ball();
  }
}

void reset() {
  Robot(&c).reset();
}

void set_sleep(int mssleep) {
  Robot(&c).set_sleep(mssleep);
}

void _draw() {
  if (!c.draw_screen()) {
    throw runtime_error("The robot walked into a wall!");
  } else {
    Robot(&c).universal_sleep();
  }
}
void create_ball(int xcor, int ycor) {
  ycor = (WereldHoogte - 3) - (ycor - 1);
  xcor = xcor - 1;
  Robot(&c)._put_ball(xcor, ycor);
  _draw();
}
void _put_ball(int xcor, int ycor) {
  Robot(&c)._put_ball(xcor, ycor);
}
void _put_wall(int xcor, int ycor) {
  Robot(&c)._put_wall(xcor, ycor);
}
void _position_robot(int xcor, int ycor) {
  Robot(&c)._position_robot(xcor, ycor);
}

void make_string_with_balls() {
  for (int i = 0; i < 48; i++) {
    _put_ball(i, 0);
    _put_ball(i, 27);
  }
  for (int i = 1; i < 27; i++) {
    _put_ball(0, i);
    _put_ball(47, i);
  }
  _draw();
}

void make_chaos_with_balls() {
  int lowest_row = (WereldHoogte - 2) - (rand () % (WereldHoogte / 2) + 3);
  for (int row = 0; row < lowest_row; row++) {
    int width = (WereldBreedte - 3) - (rand () % (WereldBreedte/2) + 1);
    for (int column = WereldBreedte - 3; column > width; column--) {
      _put_ball(column, row);
    }
  }
  _draw();
}

void make_path_with_balls() {
    Robot(&c).make_path_with_balls();
}

void make_cave() {
    Robot(&c).make_cave();
}
