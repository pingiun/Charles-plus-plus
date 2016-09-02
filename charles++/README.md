# Charles++ 

Charles++ can be run as an alternative to Charles on (almost) all OS's.
Instead of a GUI application, it's run in a console window. This makes for
great portability.

## Getting Charles++

You can use git to download Charles++, but the easiest way is to click the
green 'Clone or download' button and then download as a zip.

## Usage

You can run Charles++ with one command line argument which sets the sleep
time. A sleep time of 1000 milliseconds is useful when you clearly want to see
what happens, this is the standard value. If you want to speed it up, start
the binary with 100 milliseconds for example. In Code::Blocks you can set this
in the Project->Set program's arguments.

### Differences with official Charles 

In Charles++ the robot has to be
represented with one character, and it should also be visible if the robot is
on a ball. These are the characters if the robot is not on a ball:
- North: `^`
- East: `>`
- South: `v`
- West: `<`

If the robot is on a ball the following characters are used:
- North: `"`
- East: `]`
- South: `_`
- West `[`

When starting the Charles++, the program should ask which function you want to
run, this should be self-explanatory.

### Windows

On Windows you can use Code::Blocks to open the
`Charles++.cbp` file, this may fix problems with Windows users being able to
compiling correctly.

Windows users can also use Cygwin to compile the project with `make`.

### Linux

On most Linux distributions you can use `make` to build this project. The
binary file will then be located in bin/charles.

Of course the `Charles++.cbp` will also work on Linux in Code::Blocks.
