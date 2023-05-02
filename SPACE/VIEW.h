#include <SFML/Graphics.hpp>
using namespace sf;

View view;
void getPlayerCoordinateforview(float x, float y) { 
	float tempX = x; float tempY = y;

	if (x < 320) tempX = 320;
	if (y < 240) tempY = 240;

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты

}


void viewmap(float time) { 


	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1 * time, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1 * time);
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1 * time);
	}

}

void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f);
		
	}


	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(1920, 1080);
	}


}
