#pragma once

namespace Constants {
	constexpr int SCREEN_WIDTH = 1280;
	constexpr int SCREEN_HEIGHT = 720;

	constexpr int PLAYER_WIDTH = 42;
	constexpr int PLAYER_HEIGHT = 42;
	constexpr int PLAYER_CENTER = 21; // constant to adjust for player position that is on origin/center
	constexpr float JUMP_FORCE = -650.0f;
	constexpr float PLAYER_SPEED = 395.0f;

	constexpr int GROUND_Y = 714;
	constexpr int CAMERA_OFFSET_X = 300;
	constexpr int CAMERA_OFFSET_Y = 325;
	constexpr int CAMERA_OFFSET_GROUND_Y = 150;
	
	constexpr int GRAVITY = 2850;
	constexpr int TERMINAL_VELOCITY = 1900;

	constexpr int TILE_HEIGHT = 42;
	constexpr int TILE_WIDTH = 42;

	constexpr int BUTTON_OFFSET_X = 400;
	constexpr int BUTTON_OFFSET_Y = 560;
	constexpr int BUTTON_SPACING_HZ = 10;
	constexpr int BUTTON_SPACING_VT = 5;
	constexpr int BUTTON_WIDTH = 60;
	constexpr int BUTTON_HEIGHT = 60;

	constexpr float BG_COLOUR[3] = { 15.0f / 255.0f, 98.0f / 255.0f, 212.0f / 255.0f };
	constexpr float GROUND_COLOUR[3] = {28.0f / 255.0f, 70.0f / 255.0f, 148.0f/255.0f};
};