#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
#include <stdlib.h>
#include <time.h>
using namespace sf;

sf::String ERRORMESSAG = "FATAL ERROR: MISSED FILES! PLEASE RE-INSTAL THE GAME!";

class ItemsProp{
public:
	float x, y, a, b;
	String File;
	Image image;
	Texture texture;
	Sprite itemsprite;
	ItemsProp(String F, float a, float b, float x, float y) {
		File = F;
	

		image.loadFromFile("images/items/" + File);
		if (!image.loadFromFile("images/items/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
		else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
		image.createMaskFromColor(Color(237, 28, 36));
		texture.loadFromImage(image);
		itemsprite.setTexture(texture);
		itemsprite.setScale(a, b);
		itemsprite.setPosition(x, y);
}
	void setPosition(float x, float y) {
		itemsprite.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(itemsprite);
	}
	sf::Color getColor() const {
		return itemsprite.getColor();
	}
	void setColor(const sf::Color& color) {
		itemsprite.setColor(color);
	}
	void setTextureRect(const sf::IntRect& rect)
	{ 

		itemsprite.setTextureRect(rect);
	}
	sf::FloatRect getSpriteBounds() const {
		return itemsprite.getLocalBounds();
	}
};

class PlayerProp {
public:
	float x, y, a, b;
	String File;
	Image image;
	Texture texture;
	Sprite playerpropsprite;

	PlayerProp(String F, float a, float b, float x, float y) {
		File = F;


		image.loadFromFile("images/player/" + File);
		if (!image.loadFromFile("images/player/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
		else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
		image.createMaskFromColor(Color(237, 28, 36));
		texture.loadFromImage(image);
		playerpropsprite.setTexture(texture);
		playerpropsprite.setScale(a, b);
		playerpropsprite.setPosition(x, y);
	}
	void setPosition(float x, float y) {
		playerpropsprite.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(playerpropsprite);
	}
	sf::Color getColor() const {
		return playerpropsprite.getColor();
	}
	void setColor(const sf::Color& color) {
		playerpropsprite.setColor(color);
	}
	void setTextureRect(const sf::IntRect& rect)
	{
		playerpropsprite.setTextureRect(rect);
	}
	sf::FloatRect getSpriteBounds() const {
		return playerpropsprite.getLocalBounds();
	}
};

class MapProp {
public:
	float x, y, a, b;
	String File;
	Image image;
	Texture texture;
	Sprite mapsprite;
	MapProp(String F, float a, float b, float x, float y) {
		File = F;

		image.loadFromFile("images/map/" + File);
		if (!image.loadFromFile("images/map/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
		else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
		image.createMaskFromColor(Color(237, 28, 36));
		texture.loadFromImage(image);
		mapsprite.setPosition(x, y);
		mapsprite.setTexture(texture);
		mapsprite.setScale(a, b);
	}
	void setPosition(float x, float y) {
		mapsprite.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(mapsprite);
	}
	sf::Color getColor() const {
		return mapsprite.getColor();
	}
	void setColor(const sf::Color& color) {
		mapsprite.setColor(color);
	}
	void setTextureRect(const sf::IntRect& rect)
	{
		mapsprite.setTextureRect(rect);
	}
	sf::FloatRect getSpriteBounds() const {
		return mapsprite.getLocalBounds();
	}
};

class Info {
public:
	float x, y, a, b;
	Text text;
	Font font;




};

class MobProp {
public:
	float x, y, a, b;
	String File;
	Image image;
	Texture texture;
	Sprite mobpropsprite;

	MobProp(String F, float a, float b, float x, float y) {
		File = F;


		image.loadFromFile("images/player/" + File);
		if (!image.loadFromFile("images/player/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
		else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
		image.createMaskFromColor(Color(237, 28, 36));
		texture.loadFromImage(image);
		mobpropsprite.setTexture(texture);
		mobpropsprite.setScale(a, b);
		mobpropsprite.setPosition(x, y);
	}
	void setPosition(float x, float y) {
		mobpropsprite.setPosition(x, y);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(mobpropsprite);
	}
	sf::Color getColor() const {
		return mobpropsprite.getColor();
	}
	void setColor(const sf::Color& color) {
		mobpropsprite.setColor(color);
	}
	void setTextureRect(const sf::IntRect& rect)
	{
		mobpropsprite.setTextureRect(rect);
	}
	sf::FloatRect getSpriteBounds() const {
        return mobpropsprite.getLocalBounds();
    }
};

class Audio {
public:
	Sound sound;
	SoundBuffer soundbuffer;
	String File;
	Audio(String F) {
		File = F;
		soundbuffer.loadFromFile("sound/" + File);
		if (!soundbuffer.loadFromFile("sound/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
		else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
		sound.setBuffer(soundbuffer);
	}
	void setLoop(bool loop) {
		sound.setLoop(loop);
	}
	void play() {
		sound.play();
	}
	void stop() {
		sound.stop();
	}
	void setVolume(float x) {
		sound.setVolume(x);
	}

};