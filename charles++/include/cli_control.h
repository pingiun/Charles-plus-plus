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

#ifndef CLI_CONTROL_H
#define CLI_CONTROL_H

namespace Orientation {
enum Orientation {
  North,
  East,
  South,
  West
};
}

class cli_control {
 public:
  bool walls[48][28];
  bool balls[48][28];
  int milli;
  int robotx;
  int roboty;
  Orientation::Orientation orientation;
  cli_control();
  void reset();
  char getrobotchar(bool);
  bool draw_screen();

 protected:

 private:
};

#endif // CLI_CONTROL_H
