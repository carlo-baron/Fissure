#include "Input.hpp"
#include <raylib.h>

/**
 * @brief Maps A and D key inputs to -1, 1, or 0 if no input detected.
 * @return int The direction scalar either -1, 1 or 0 
 */
int Input::GetHorizontalAxis(){
	float left = IsKeyDown(KEY_A) ? -1 : 0;
	float right = IsKeyDown(KEY_D) ? 1 : 0;

	return left + right;
} 

/**
 * @brief Maps W and S key inputs to -1, 1, or 0 if no input detected.
 * @return int The direction scalar either -1, 1 or 0 
 */
int Input::GetVerticalAxis(){
	float up = IsKeyDown(KEY_W) ? -1 : 0;
	float down = IsKeyDown(KEY_S) ? 1 : 0;

	return up + down;
} 
