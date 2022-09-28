#pragma once

namespace Constants {
	constexpr int SCREEN_WIDTH = 1280;
	constexpr int SCREEN_HEIGHT = 720;

	constexpr int PLAYER_WIDTH = 42;
	constexpr int PLAYER_HEIGHT = 42;
	constexpr int PLAYER_CENTER = 21; // constant to make SnapToGrid object center on mouse

	constexpr int GROUND_Y = 600;
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
};