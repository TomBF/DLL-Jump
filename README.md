# DLL-Jump
![App Screenshot](/bin/screenshot.png)

  
DLL-Jump is an application that simulates a scrolling 2D world similiar to Doodle Jump. It features a player (green cirlce) that is able to jump on obstacles (white lines) and dies on contact with enemies (purple circles) or falls below the level border.  

The environment and the controls are implemented by a DLL-based plugin architecture. It runs on Windows and is written in C++ and CLR. Rendering is done pixel-based on the CPU.

## Evaluator
bin/Evaluator.exe  
Program that ticks and renders a 2D world by a provided DLL. It moves a player that is controlled via a controller provided by another DLL. All DLLs can be loaded and replaced while running. **The source of the evaluator application itself is not provided**. The program can be extended by providing features within the plugins.

### Parameter
Following arguments are supported:  
/world [path to world dll]  
/controller [path to controller dll]  
/timestep [frame timestep, lower for faster simulation]  
See also the provided batch files for usage.

## Plugins
The program supports two types of plugins:
- World DLL  
Builds and simulates a scrolling 2D World, featuring bases, enemies and players.  
For implementation details see WorldInterface.h
- Controller DLL  
Controls the main player by providing jump and side movemements.  
For implementation details see ControllerInterface.h

## Reference Implementations
The project includes three reference implementations, located in the plugins folder:
### DefaultWorld.dll
A horizontal scrolling 2D world with static obstacles and static enemies. 
### KeyboardController.dll
A controller that fetches <space> and <arrow> keys to control the main players.
### AIController.dll
A simple ai controller that automatically tries to climp as high as possible.



