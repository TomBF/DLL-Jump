# DLL-Jump
An application that simulates a simple world similiar to Doodle Jump.
The environment and the controls are implemented by a DLL based plugin architecture.
It runs on Windows and is written in C++ and CLR

bin/Evaluator.exe
Program that ticks and renders a 2D world provided by a DLL and a controller provided by another DLL

## Parameter
Following arguments are supported:
> /world [path to world dll]
> /controller [path to controller dll]
> /timestep [frame timestep, lower for faster simulation]

The program supports two types of plugins:
### World DLL
Builds and simulates a scrolling 2D World, featuring bases, enemies and players
For implementation details see WorldInterface.h

### Controller DLL
Controls the main player by providing jump and side movemements
see ControllerInterface.h

## Reference Implementations
The project include 3 reference implementions to be found in the plugin folder:
### DefaultWorld
A horizontal scrolling 2D world with static obstacles and enemies. The horizontal size is limited to ~5000 pixel the level is deterministic
### KeyboardController
A controller that fetches <space> and <arrow> keys to control the main players
### AIController
A simple ai controller that automatically tries to climp as heigh as possible



