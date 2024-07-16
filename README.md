# Lem-in

This project aims to simulate an ant colony...

Our program will take rooms (identified by name and x, y coordinates) as input, as well as the connections between these rooms.

The goal of the program is to: for the given 'n' number of ants, find the shortest path(s) that allow all the ants to travel from the room ##start to the room ##end using the fewest possible number of turns.

The following rules must be respected:
  - There can be no more than one ant per room (except for 'start' and 'end').
  - All ants start in the room ##start.
  - Each turn, you can move each ant only once, and it must follow a connection (the destination room must be free).
  
Example of a valid file:
  
```
5         //number of ants
1 0 2     ///////////////
##start   //
0 2 0     //  Declaration of rooms (name x y)
##end     //  ##start and ##end define a status for the room declared on the next line
4 2 6     //  here the room named '0' will be the start room
2 4 2     //
3 4 4     ////////////////
0-1       ////////////////
0-2       //
2-3       //  Declaration of connections between rooms (room_name1 - room_name2)
3-4       //
4-1       ////////////////
```

A makefile is provided to compile the program.

Files defining the rooms are available in the 'maps_test' folder.
Run the program like this: ./lem-in < maps_test/nc

To make the output more human-readable, a visualization is available with this project (with a particular theme)!

First, run the command: sh brew_check.sh - this script will install the necessary components for the visualization to work (this may take some time).

Then, a simple make re will set everything up correctly.

After that, run the same command as before followed by a '|' and the executable ./display (note there is sound!):
./lem-in < maps_test/nc | ./display

The '+' and '-' keys on your numeric keypad will increase and decrease the speed.

Menu music: Propellerheads - Spybreak (Bullet time!!)

Visualization music: Deftones - My Own Summer (instrumental only)

Some screenshots:

Menu :
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image1.png)

Graphical representation of the algorithmic method used:
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image2.png)

The ants (yes, they are ants) traveling from start to end following the found paths:
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image3.png)
