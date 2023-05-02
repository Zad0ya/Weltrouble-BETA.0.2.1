#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
public:
	float x, y, w, h, dx, dy, speed = 0;
	int dir = 0;
	String File;
	Image image;
	Texture texture;
	Sprite playersprite;

	

	Player(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("images/player/" + File);
		image.createMaskFromColor(Color(237, 28, 36));
		texture.loadFromImage(image);
		playersprite.setTexture(texture);
		x = X; y = Y;
		playersprite.setTextureRect(IntRect(0, 0, w, h));
		
	}

	float getDistanceTo(sf::Vector2f point) const {
		sf::Vector2f playerPos = getPosition();
		float dx = playerPos.x - point.x;
		float dy = playerPos.y - point.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	
	sf::Vector2f getPosition() const {
		return playersprite.getPosition();
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		playersprite.setPosition(x, y);
	}
		float getPlayerCoordinateX() {	
		return x;
	}
	float getPlayerCoordinateY() {	 	
		return y;
	}

};
