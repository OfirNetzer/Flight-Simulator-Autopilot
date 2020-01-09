
# Flight Simulator (Autopilot)

In this project we implemented client and server that work with "FlightGear" simulator. Their main purpose is to make the the flight simulator airplane fly automatically. Our program receives a file with a script to run the simulator, and it creates a Lexer out of it, meaning it splits the content of the file into tokens, which are then sent to the Parser, there they get translated into commands. Each command is a class that inherits from the Command interface, by which implementing the Command Pattern. We have a symbol table, which is basically two maps, that hold the values of the variables that the simulator uses. One map is for saving the value of each variable, and the other uses the path of each variable as its key, and the variable as its value. 

Client and server: We open sockets for a client and for a server. The number that is received for the client socket is passed to the Symbol Table class, which in its turn, whenever it sees a '=' or '->', updates (sends) the relevant value in the simulator. For the server, we send the socket number to a function that runs in a thread. There there is a loop that runs as long as the parser has not finished parsing all of the file, and it listens to the simulator, waiting to receive updates in the values of the variables. Whenever it gets such an update (basically happens all the time), it goes to the variable's path in the map, and there updates the variable's value.

Once the variable alt is equal to 1000, the program prints "done", and the Parser stops parsing. The plane will continue flying.

# Code Files

**Command** *(Virtual Class)* **-** 
**connectCommand** *(client)* **-**  (inherit from "Command" Class)
Opens a socket to connect as a client to the simulator, and sends the socket identifier to the Symbol Table class.
**openServerCommand** *(server)* **-** (inherit from "Command" Class) Opens a socket to connect to the simulator as a server. Opens a thread that runs a function that listens constantly to the simulator, updating values it receives from it.
**Lexer -** Splits the content of the file into tokens.
**Parser -** Runs through the lexer, and associates each line in the original file, to a specific command.
**Var -** Each variable is a Var object, and has the fields: name, sim (=path), direction, and value.
**symTable** *(Symbol Table)* **-** Holds two maps: uiMap- key=name of the variable, value= its Var object. siMap- key= path, value= its var object. 
Moreover, it creates new variables while reading the raw data (that located in the lexer) and updates the values of each variable 
while the simulator is running. 
**ex1** *(Interpreter)* **-** Translates a mathematical expression into a double.
**Expression.h -** Interface for ex1.
**Exp -** Takes an expression with variables, assigns them their value from the map, and uses ex1 to solve them.
**Flag.h -** Singleton that holds a flag, which is used to determine whether the file is fully parsed or not (used in the server while loop).
**Substring -** Creates a substring, with a given delimiter.
**Mutex -** Holds a singleton mutex object.


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
eyJoaXN0b3J5IjpbMjExMDc4NjY0N119
-->
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjI0ODQxOTk1XX0=
-->