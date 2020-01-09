# Flight Simulator (Autopilot)

In this project we implemented client and server that work with "FlightGear" simulator. Their main purpose is to make the the flight simulator airplane fly automatically. Our program receives a file with a script to run the simulator, and it creates a Lexer out of it, meaning it splits the content of the file into tokens, which are then sent to the Parser, there they get translated into commands. Each command is a class that inherits from the Command interface, by which implementing the Command Pattern. We have two maps, that hold the values of the variables that the simulator uses. One map is for saving the value of each variable, and the other uses the path of each variable as its key, and the variable as its value. In addition we hold a Symbol Table, which ----- OFIR to complete what the symbol table does -----

Client and server: We open sockets for a client and for a server. The number that is received for the client socket is passed to the Symbol Table class, which in its turn, whenever it sees a '=' or '->', updates (sends) the relevant value in the simulator. For the server, we send the socket number to a function that runs in a thread. There there is a loop that runs as long as the parser has not finished parsing all of the file, and it listens to the simulator, waiting to receive updates in the values of the variables. Whenever it gets such an update (basically happens all the time), it goes to the variable's path in the map, and there updates the variable's value.

Once the variable alt is equal to 1000, the program prints "done", and the Parser stops parsing. The plane will continue flying.

# Code Files

**Client -**
**Server -**
**Lexer -**
**Parser -**
**Symbol Table** *(symTable.cpp)* **-**
StackEdit stores your files in your browser, which means all your files are automatically saved locally and are accessible **offline!**

## Design patterns used in code

Command Pattern - Having one Command.h interface, that holds an "execute" method, and multiple different command classes that inherit it, each implementing "execute" in their unique way.

# Downloads

We need to download and install the application "FlightGear". In addition, we need a text file with the code, which will be one of the arguments, and a xml file with all the variable names in the simulator, which we will put in the usr/share/games/flightfear/Protocol folder.

## Installing FlightGear

Instructions for downloading can be found on the website  https://www.flightgear.org/download/main-program/

# Compiling the Code
 
To compile, we need to provide a text file that lists all of the commands for the plane to be able to fly. It will be provided as a program argument.

To compile from the command line:
g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

# Running the Program
 
For the program to run well, first we compile and then run the program. Once we see "Server is now listening...", we open and run the FlightGear application, which should connect with our program, through the server we opened. Once we have a  connection between the simulator and our program, the plane should start to move, and shortly after, takeoff and fly. 
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTQwODk5NjcxNl19
-->