#include <SFML/Graphics.hpp>

void Indicatorcalc(sf::Sprite Indicators, sf::RenderWindow& window, float energyLevel, float indicatorsPosX, float indicatorsPosY, float HPLevel,
	float indicatorsHPPosY, bool& is_Player_Can_Run, float& playerSpeedNormal, float& playerSpeedRunning) {
	sf::FloatRect spriteSize = Indicators.getLocalBounds();
	float spriteWidth = spriteSize.width;
	float spriteHeight = spriteSize.height;

		sf::RectangleShape Energy(sf::Vector2f(spriteSize.width * 0.5f - 114 - 1 * (1 - energyLevel), spriteSize.height * 0.5f - 133));
		Energy.setFillColor(sf::Color(247, 213, 40, 255));
		Energy.setPosition(indicatorsPosX, indicatorsPosY);
		window.draw(Energy);


		sf::RectangleShape HP(sf::Vector2f(spriteSize.width * 0.5f - 114 - 1 * (1 - HPLevel), spriteSize.height * 0.5f - 133));

		if (HP.getSize().x >= 111.5f) {
			HP.setFillColor(sf::Color(108, 210, 105, 255));
			is_Player_Can_Run = true;
			playerSpeedNormal = 0.1;
			playerSpeedRunning = 0.2;
		}
		else if (HP.getSize().x > 55.2f) {
			HP.setFillColor(sf::Color(255, 188, 0, 255));
			is_Player_Can_Run = true;
			playerSpeedNormal = 0.05;
			playerSpeedRunning = 0.1;
		}
		else {
			HP.setFillColor(sf::Color(229, 0, 0, 255));
			is_Player_Can_Run = false;
			playerSpeedNormal = 0.03;
		}


		HP.setPosition(indicatorsPosX, indicatorsHPPosY);
		window.draw(HP);
	
}
