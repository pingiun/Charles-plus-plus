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

#include "cli_control.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

cli_control::cli_control() {
  reset();
}

void cli_control::reset(){
  for (int i = 0; i < 48; i++) {
    for (int j = 0; j < 28; j++) {
      walls[i][j] = false;
    }
  }
  for (int i = 0; i < 48; i++) {
    for (int j = 0; j < 28; j++) {
      balls[i][j] = false;
    }
  }
  milli = 1000;
  robotx = 0;
  roboty = 0;
  orientation = Orientation::East;
}

char cli_control::getrobotchar(bool ball) {
  if (!ball) {
    switch (orientation) {
    case Orientation::North:
      return '^';
    case Orientation::East:
      return '>';
    case Orientation::South:
      return 'v';
    case Orientation::West:
      return '<';
    default:
      throw runtime_error("Nonreachable code reached");
    }
  } else {
    switch (orientation) {
    case Orientation::North:
      return '"';
    case Orientation::East:
      return ']';
    case Orientation::South:
      return '_';
    case Orientation::West:
      return '[';
    default:
      throw runtime_error("Nonreachable code reached");
    }
  }
}

bool cli_control::draw_screen() {
  // Eerst collisions checken
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 48; j++) {
      if (walls[j][i] && j == robotx && i == roboty) {
        return false;
      }
    }
  }
  if (robotx < 0 || robotx > 47 || roboty < 0 || roboty > 28) {
    return false;
  }
  // We nemen aan dat er om het veld altijd muren zijn
  stringstream stream;
  stream << "+";
  for (int i = 0; i < 48; i++) {
    stream << "-";
  }
  stream << "+" << endl;

  for (int i = 0; i < 28; i++) {
    stream << "|";
    for (int j = 0; j < 48; j++) {
      if (walls[j][i]) {
        stream << "*";
      } else if (balls[j][i] && j == robotx && i == roboty) {
        stream << getrobotchar(true);
      } else if (balls[j][i]) {
        stream << "o";
      } else if (j == robotx && i == roboty) {
        stream << getrobotchar(false);
      } else {
        stream << ".";
      }
    }
    stream << "|" << endl;
  }

  stream << "+";
  for (int i = 0; i < 48; i++) {
    stream << "-";
  }
  stream << "+" << endl;
  cout << stream.rdbuf();
  return true;
}
