#include "Spritesheet.h"

Spritesheet::Spritesheet(std::string file, float tW, float tH, float sp, int columns, int size, float fileW, float fileH) {
	this->tileHeight = tH;
	this->tileWidth = tW;
	this->spacing = sp;

	int row=0, count=0;
	while (count < size) {
		for (int column = 0; column < columns; column++) {
			float imgX = (column * tW) + (column * sp); // top left texture x-coord
			float imgY = (row * tH) + (row * sp);		// top left texture y-coord

			sprites.push_back(new Sprite(file, imgX, imgY, tW, tH, fileW, fileH, row, column, count));
			count++;
			if (count > size - 1) {
				break;
			}
		}
		row++; 
	}
}