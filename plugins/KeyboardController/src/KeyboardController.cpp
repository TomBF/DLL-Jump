#include <Windows.h>
#include "KeyboardController.h"
#include "../../../src/WorldCanvas.h"

bool KeyboardController::inputJump() const 
{
	/// jump if space is pressed
	return (GetKeyState(VK_UP) & 0x8000) != 0;
}
float KeyboardController::inputSide() const 
{
	/// push left or right if arrow keys are pressed

	if ((GetKeyState(VK_LEFT) & 0x8000) != 0)
		return -1.0f;
	if ((GetKeyState(VK_RIGHT) & 0x8000) != 0)
		return 1.0f;
	return 0.0f;
}
void KeyboardController::onTick(float time_step, const WorldInterface& world) 
{
	return;
}

void KeyboardController::onDraw(WorldCanvas& canvas) 
{ 

};



/// export KeyboardController from DLL
extern "C"
{
	__declspec(dllexport) ControllerInterface* createController()
	{
		return new KeyboardController();
	}
}
