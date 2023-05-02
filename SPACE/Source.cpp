#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>
#include <locale>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "ANIMATION_UI.h"
#include "PLAYER.h"
#include "PLAYER_INDICATORS.h"
#include "INCLUDE.h"
#include "ItemsGenerator.h"
#include "VIEW.h"
#include "MAP_MARS.h"
#include "LANGUAGE_GLOBAL.h"
#include "NPC.h"
#include "SOUND.h"
#include "MENUBAR.h"
#include "DAMAGE.h"

using namespace sf;

int WEAPON_CLASS_PISTOL_GENERATION(int min, int max)
{
	srand(time(NULL));
	int num = min + rand() % (max - min + 1);

	return num;
}

int main()

{
	LanguageGLOBAL menu;

	int xPistol, yPistol;
	int const CELL_SIZE = 151;
	int trueStatus = 0;
	int cellSelected = 0;
	int selectedX = 0;
	int selectedY = 0;
	int gameMusic;
	int gameVolume;
	int HEIGHT_INVENTORY = 0, WIDTH_INVENTORY = 0, MAX_WEIGHT = 0;
	int dir = 0;

	bool is_Stat_Open = false;
	bool is_Settings_Open = false;
	bool settingsUpdate_bool = true;
	bool isWALK_SOUNDPlaying = false;
	bool isKeyPressed = false;
	bool is_Pistol_Collected = false;
	bool is_GUN_Pistol_Selected = false;
	bool is_Inventory_Opened = false;
	bool is_Small_INVENTORY = false;
	bool is_Mid_INVENTORY = false;
	bool is_Adv_INVENTORY = true;
	bool is_Big_INVENTORY = false;
	bool is_Item_Selected = false;
	bool is_Game_Paused = false;
	bool is_Player_In_Zone_For_Attack = false;
	bool is_Player_Can_Run = true;

	float indicatorsPosX;
	float indicatorsPosY;
	float indicatorsHPPosY;
	float indicatorSpritePosX;
	float indicatorSpritePosY;
	float currentFrame = 0;
	float energyLevel = 1.0f;
	float timeSinceLastEnergyDrain = 0.f;
	float HPLevel = 1.0f;
	float pistolRadius = 123.f;
	float playerSpeedNormal = 0.1;
	float playerSpeedRunning = 0.2;

	const float UPDATE_TIME_SETTINGS = 2.f;
	const float ENERGY_RECOVERY_TIME = 3.f;
	const float ENERGY_RECOVERY_RATE = 0.03f;
	const float HP_RECOVERY_TIME = 30.f;
	const float HP_RECOVERY_RATE = 0.003f;
	const float DAMAGE_RECOVERY_RATE = 2.f;

	const sf::String ERRORMESSAG = "FATAL ERROR: MISSED FILES! PLEASE RE-INSTAL THE GAME!";
	String Check = "Is_";

	std::vector<bool> inventoryGUNS = { false, false, false, false };
	std::vector<bool> inventoryPROPS = { false, false, false, false };
	std::vector<std::string> inventory_Set_Position_Vector;




	std::time_t now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);
	int number;
	number = WEAPON_CLASS_PISTOL_GENERATION(0, 5000);
	xPistol = number;
	yPistol = number + 100;

	Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
	Text GAME_Version_Information("PRE-ALPHA BUILD. VERSION 0.2.1. PLEASE REPORT ALL BUGS.", font);
	GAME_Version_Information.setCharacterSize(20);
	GAME_Version_Information.setStyle(sf::Text::Bold);

	Font mainfont;
	mainfont.loadFromFile("files/fonts/mainpixel.ttf");
	Text Font_Main("", mainfont);
	Font_Main.setCharacterSize(20);
	Font_Main.setStyle(sf::Text::Bold);
	Font_Main.setFillColor(sf::Color::Black);

	Text Font_Main2("", mainfont);
	Font_Main2.setCharacterSize(25);
	Font_Main2.setStyle(sf::Text::Bold);
	Font_Main2.setFillColor(sf::Color::Black);

	Audio damagePlayer("damageplayer.wav");
	Audio WALK_SOUND("walk.wav");
	Audio Pick("pick.wav");
	sf::Sound sounds[] = { Pick.sound, WALK_SOUND.sound, damagePlayer.sound};
	MapProp s_map("marsprops.png", 1, 1, 50, 30);
	ItemsProp GUN_Pistol("PistolIcon.png", 0.3f, 0.3f, 0, 0);
	ItemsProp GUN_Pistol_ICON("MapgenerPist.png", 0.1f, 0.1f, xPistol, yPistol);
	sf::Color colorpstol = GUN_Pistol_ICON.getColor();
	colorpstol.a = 200;
	GUN_Pistol_ICON.setColor(colorpstol);
	PlayerProp Inventory_Icons("invcase.png", 0.5f, 0.5f, 0, 0);
	PlayerProp Menubar("inter.png", 0.5f, 0.5f, 0, 0);
	PlayerProp Menubar_Selection("SelectionFrame.png", 0.5f, 0.5f, 0, 0);
	PlayerProp Indicators("Indicators.png", 0.5f, 0.5f, 0, 0);
	PlayerProp Menubar_BIG("Menu_BIG.png", 0.5f, 0.5f, 0, 0);
	PlayerProp Menubar_BOX("MENU_ICONS_BOX.png", 1, 1, 0, 0);
	Indicators.playerpropsprite.setTextureRect(IntRect(330, 347, 670, 333));
	//670,333

	Player player("herobeta.png", 2500, 2500, 112, 178);
	sf::FloatRect playerHitBox = player.playersprite.getGlobalBounds(); //TEMPORARY ONLY FOR TEST PURPOSE 
	NPCclassAnimal Kafer("KaferMob.png", 1930, 1930, 615, 484);
	sf::FloatRect kaferHitBox = Kafer.npc_sprite.getGlobalBounds();  //TEMPORARY ONLY FOR TEST PURPOSE 

	Kafer.npc_sprite.setScale(0.2f, 0.2f); 
	sf::FloatRect spriteSize = Indicators.playerpropsprite.getLocalBounds();
	float spriteWidth = spriteSize.width;

	RenderWindow window(VideoMode(1920, 1080), "Weltrouble BETA V 0.2");
	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	sf::RectangleShape rectinv(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	sf::RectangleShape rect2(sf::Vector2f(window.getSize().x / 4, window.getSize().y));
	sf::RectangleShape rect(sf::Vector2f(window.getSize().x, window.getSize().y));
	sf::View viewinv(window.getView());
	viewinv.setCenter(window.getSize().x / 2, window.getSize().y / 2);


	Clock clock;
	Clock NPC;
	Clock timeFromLastRun;
	Clock changeDir;
	Clock timeFromLastDamage;
	while (window.isOpen())


	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, viewinv);

		float times = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		times = times / 800;
		Event event;

		float timenpc = NPC.getElapsedTime().asMicroseconds();
		NPC.restart();
		timenpc = timenpc / 800;

		if (changeDir.getElapsedTime().asSeconds() > 3) {
			if (std::rand() % 2 == 0) {
				dir = std::rand() % 4;
			}
			changeDir.restart();
		}

		while (window.pollEvent(event))

		{
			switch (event.type)
			{
			case::Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				if (event.key.code == sf::Keyboard::I) {
					is_Inventory_Opened = !is_Inventory_Opened;
					if (is_Inventory_Opened) {
						window.waitEvent(event);
					}
				}
				if (event.key.code == sf::Keyboard::Escape) {
					is_Game_Paused = !is_Game_Paused;
					window.waitEvent(event);
				}
				break;
			default:
				break;
			}
		}

		if (settingsUpdate_bool) {

			getPlayerCoordinateforview(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());
			indicatorsPosX = Indicators.playerpropsprite.getPosition().x + 95;
			indicatorsPosY = Indicators.playerpropsprite.getPosition().y + 113;
			indicatorsHPPosY = indicatorsPosY - 82;
			indicatorSpritePosX = view.getCenter().x - (window.getSize().x - window.getSize().x / 1.9);
			indicatorSpritePosY = view.getCenter().y + 250;

			std::fstream savesettings("saved/savedsettings.txt", std::ios::in);
			if (savesettings.is_open()) {
				std::string savedinfo1;
				std::getline(savesettings >> std::ws, savedinfo1);
				menu.setLanguage(savedinfo1);

				std::string savedinfo2;
				std::getline(savesettings >> std::ws, savedinfo2);
			    gameVolume = std::stoi(savedinfo2);
				WALK_SOUND.setVolume(gameVolume);
				Pick.setVolume(gameVolume);
				damagePlayer.setVolume(gameVolume);

				std::string savedinfo3;
				std::getline(savesettings >> std::ws, savedinfo3);
				gameMusic = std::stoi(savedinfo3);

			}
			savesettings.close();
			!settingsUpdate_bool;
		}

		window.clear();
		
		// MAP MAIN 
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(42, 34, 652, 652)); //texture main
				if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(803, 35, 652, 652)); //texture second
				s_map.setPosition(j * 645, i * 610); //map generation 
				window.draw(s_map.mapsprite);
			}

		// MENUBAR
		if (is_Game_Paused) {
			DrawPauseMenu(window, viewinv, rect, Menubar.playerpropsprite, Font_Main, mousePos, mousePosView, is_Game_Paused, Menubar_Selection.playerpropsprite,
			is_Stat_Open, is_Settings_Open, Menubar_BIG.playerpropsprite, Menubar_BOX.playerpropsprite, gameMusic, gameVolume, menu, settingsUpdate_bool);
		}


		if (is_Small_INVENTORY == true) { HEIGHT_INVENTORY = 2; WIDTH_INVENTORY = 3; MAX_WEIGHT = 45; }
		if (is_Mid_INVENTORY == true) { HEIGHT_INVENTORY = 4; WIDTH_INVENTORY = 5; MAX_WEIGHT = 90; }
		if (is_Adv_INVENTORY == true) { HEIGHT_INVENTORY = 5; WIDTH_INVENTORY = 7; MAX_WEIGHT = 125; }
		if (is_Big_INVENTORY == true) { HEIGHT_INVENTORY = 7; WIDTH_INVENTORY = 10; MAX_WEIGHT = 220; }
		int** INVENTORY_AVAI = new int* [HEIGHT_INVENTORY];
		for (int i = 0; i < HEIGHT_INVENTORY; i++) {
			INVENTORY_AVAI[i] = new int[WIDTH_INVENTORY];
		}
		inventory_Set_Position_Vector.resize(HEIGHT_INVENTORY * WIDTH_INVENTORY);
		if (!is_Game_Paused) {
			window.setView(viewinv);
			int xOffset = (window.getSize().x - (WIDTH_INVENTORY * CELL_SIZE)) / 2;
			int yOffset = (window.getSize().y - (HEIGHT_INVENTORY * CELL_SIZE)) / 2;
			if (is_Inventory_Opened == true) {
				rect.setFillColor(sf::Color(0, 0, 0, 128));
				window.setView(viewinv);
				window.draw(rect);

				for (int i = 0; i < HEIGHT_INVENTORY; i++) {
					for (int j = 0; j < WIDTH_INVENTORY; j++) {
						Inventory_Icons.setTextureRect(IntRect(159, 95, 304, 304));
						Inventory_Icons.setPosition(j * CELL_SIZE + xOffset, i * CELL_SIZE + yOffset);

						window.draw(Inventory_Icons.playerpropsprite);
					}

				}
				for (bool b : inventoryGUNS) {
					for (int i = 0; i < inventoryGUNS.size(); i++) {
						int Position_Calculation_Inventory_X = 1;
						int Position_Calculation_Inventory_Y = 1;
						if (inventoryGUNS[i] == true) {
							if (i == 0) {
								GUN_Pistol.setPosition(xOffset - 30 + ((Position_Calculation_Inventory_X * 151) - 151), (yOffset - 30 + (Position_Calculation_Inventory_Y * 151) - 151));
								inventory_Set_Position_Vector.insert(inventory_Set_Position_Vector.begin() + Position_Calculation_Inventory_X - 1, "GUN_Pistol");
								window.draw(GUN_Pistol.itemsprite);
								Position_Calculation_Inventory_X++;
								if (Position_Calculation_Inventory_X > WIDTH_INVENTORY) Position_Calculation_Inventory_X = 0; Position_Calculation_Inventory_Y++;
							}
						}
					} //Отсутствует точная закрепленна позиция предмета в инвентаре(при открытии инвентаря заново если вещи были подобраны
					// в порядке не соответствующем порядку проверки
				}
				for (int i = 0; i < HEIGHT_INVENTORY; i++) {
					for (int j = 0; j < WIDTH_INVENTORY; j++) {
						sf::Vector2f cellPos = sf::Vector2f(j * CELL_SIZE + xOffset, i * CELL_SIZE + yOffset);
						if (mousePosView.x >= cellPos.x && mousePosView.x <= cellPos.x + CELL_SIZE &&
							mousePosView.y >= cellPos.y && mousePosView.y <= cellPos.y + CELL_SIZE) {  // TASK fix double inventory items
							rectinv.setFillColor(sf::Color(255, 255, 255, 70));
							rectinv.setPosition(cellPos.x, cellPos.y);
							window.draw(rectinv);
							if (Mouse::isButtonPressed(Mouse::Left)) {
								is_Item_Selected = true; selectedX = cellPos.x; selectedY = cellPos.y;
								int row = (mousePosView.y - yOffset) / CELL_SIZE;
								int col = (mousePosView.x - xOffset) / CELL_SIZE;
								int cellIndex = row * WIDTH_INVENTORY + col;
								for (int i = 0; i < inventory_Set_Position_Vector.size(); i++) {
									if (i == cellIndex) {
										animatePanel_LEFT_TOP(window, Menubar.playerpropsprite, Font_Main2, menu.getString("INVENTORY_ITEM_SELECTED"));
										Check += inventory_Set_Position_Vector[i] += "_Selected";
										bool b = Check == "true";
										if (is_GUN_Pistol_Selected) std::cout << Check.toAnsiString();

									}
								}
							}
							if (Mouse::isButtonPressed(Mouse::Right) or Keyboard::isKeyPressed(Keyboard::G)) {
								if (cellPos.x == selectedX && cellPos.y == selectedY) {
									is_Item_Selected = false; selectedX = 0; selectedY = 0; Check = "Is_";
								}
								int row = (mousePosView.y - yOffset) / CELL_SIZE;
								int col = (mousePosView.x - xOffset) / CELL_SIZE;
								int cellIndex = row * WIDTH_INVENTORY + col;
								for (int i = 0; i < inventory_Set_Position_Vector.size(); i++) {
									if (i == cellIndex && inventory_Set_Position_Vector[i] != ' ') {
										Pick.setVolume(30);
										Pick.play();
										animatePanel_LEFT_TOP(window, Menubar.playerpropsprite, Font_Main2, menu.getString("INVENTORY_DROPPED"));
										GUN_Pistol_ICON.setPosition(player.getPlayerCoordinateX(), player.getPlayerCoordinateY()); //не работает последующий подбор птому что появляется только фотка без обновления пистольх

									}
								}
							}
						}
					}
				}
				if (is_Item_Selected) {
					rectinv.setFillColor(sf::Color(0, 0, 0, 90));
					rectinv.setPosition(selectedX, selectedY);
					window.draw(rectinv);
				}
			}
		}



		if (isWALK_SOUNDPlaying && is_Inventory_Opened || is_Game_Paused) {
			WALK_SOUND.stop();
			isWALK_SOUNDPlaying = false;
			WALK_SOUND.setLoop(false);
		}
		
		//movemainchar
		if (!is_Inventory_Opened && !is_Game_Paused) {

			if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
				player.playersprite.setRotation(0.f);
				player.playersprite.rotate(0.f);
				float rotation = player.playersprite.getRotation();
			}
			if (!is_Inventory_Opened && !is_Game_Paused) {
				if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
					if ((Keyboard::isKeyPressed(Keyboard::LShift)) && spriteSize.width * 0.5f - 114 - 1 * (1 - energyLevel) >= 0
						&& is_Player_Can_Run) {
						player.dir = 0; player.speed = playerSpeedRunning;
						currentFrame += 0.006 * times;
						player.playersprite.setRotation(10.f);
						player.playersprite.rotate(-4.f);
						float rotation = player.playersprite.getRotation();
						energyLevel -= 0.1f;
						timeFromLastRun.restart();
					}
					else {
						player.dir = 0; player.speed = playerSpeedNormal;
						currentFrame += 0.005 * times;
						player.playersprite.setRotation(0.f);
						player.playersprite.rotate(0.f);
						float rotation = player.playersprite.getRotation();
					}
					if (currentFrame > 4) currentFrame -= 4;
					player.playersprite.setTextureRect(IntRect(128 * int(currentFrame), 386, 112, 179));
					getPlayerCoordinateforview(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());
				}


				if (((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))) {
					if ((Keyboard::isKeyPressed(Keyboard::LShift)) && spriteSize.width * 0.5f - 114 - 1 * (1 - energyLevel) >= 0 
						&& is_Player_Can_Run) {
						player.dir = 0; player.speed = -playerSpeedRunning;
						currentFrame += 0.006 * times;
						player.playersprite.setRotation(-10.f);
						player.playersprite.rotate(4.f);
						float rotation = player.playersprite.getRotation();
						energyLevel -= 0.1f;
						timeFromLastRun.restart();
					}
					else {
						player.dir = 0; player.speed = -playerSpeedNormal;
						currentFrame += 0.005 * times;
						player.playersprite.setRotation(0.f);
						player.playersprite.rotate(0.f);
						float rotation = player.playersprite.getRotation();
					}
					if (currentFrame > 4) currentFrame -= 4;
					player.playersprite.setTextureRect(IntRect(128 * int(currentFrame), 192, 112, 179));
					getPlayerCoordinateforview(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());

				}

				if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
					if ((Keyboard::isKeyPressed(Keyboard::LShift)) && spriteSize.width * 0.5f - 114 - 1 * (1 - energyLevel) >= 0
						&& is_Player_Can_Run) {
						player.dir = 3; player.speed = playerSpeedRunning;
						currentFrame += 0.006 * times;
						energyLevel -= 0.1f;
						timeFromLastRun.restart();
					}
					else {
						player.dir = 3; player.speed = playerSpeedNormal;
						player.playersprite.setRotation(0.f);
						player.playersprite.rotate(0.f);
						float rotation = player.playersprite.getRotation();
						currentFrame += 0.005 * times;
					}
					if (currentFrame > 4) currentFrame -= 4;
					player.playersprite.setTextureRect(IntRect(128 * int(currentFrame), 577, 112, 179));
					getPlayerCoordinateforview(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());
				}

				if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
					if ((Keyboard::isKeyPressed(Keyboard::LShift)) && spriteSize.width * 0.5f - 114 - 1 * (1 - energyLevel) >= 0
						&& is_Player_Can_Run) {
						player.dir = 2; player.speed = playerSpeedRunning;
						currentFrame += 0.006 * times;
						energyLevel -= 0.1f;
						timeFromLastRun.restart();
					}
					else {
						player.dir = 2; player.speed = playerSpeedNormal;
						currentFrame += 0.005 * times;
						player.playersprite.setRotation(0.f);
						player.playersprite.rotate(0.f);
						float rotation = player.playersprite.getRotation();

					}
					if (currentFrame > 4) currentFrame -= 4;
					player.playersprite.setTextureRect(IntRect(128 * int(currentFrame), 2, 112, 179));
					getPlayerCoordinateforview(player.getPlayerCoordinateX(), player.getPlayerCoordinateY());
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Left)
				|| Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)
				|| Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			{
				if (!isKeyPressed)
				{
					isKeyPressed = true;
					if (!isWALK_SOUNDPlaying)
					{
						WALK_SOUND.play();
						isWALK_SOUNDPlaying = true;
						WALK_SOUND.setLoop(true);
					}
				}
			}

			else
			{
				isKeyPressed = false;
				if (isWALK_SOUNDPlaying)
				{
					WALK_SOUND.stop();
					isWALK_SOUNDPlaying = false;
					WALK_SOUND.setLoop(false);
				}
			}

		}

		// подбор
		sf::Vector2f pointToCheck(xPistol + 130, yPistol);
		if (player.getDistanceTo(pointToCheck) <= pistolRadius) {
			GUN_Pistol_ICON.setPosition(-1000.f, -1000.f);
			Pick.setVolume(30);
			Pick.play();
			xPistol = -1000;
			yPistol = -1000;
			is_Pistol_Collected = true;
			inventoryGUNS[0] = true;
		}

		// Recovery
		if (timeFromLastRun.getElapsedTime().asSeconds() > ENERGY_RECOVERY_TIME && !is_Game_Paused && !is_Inventory_Opened) {
			energyLevel += ENERGY_RECOVERY_RATE;
			if (energyLevel >= 1.f) {
				energyLevel = 1.f;
			}
		}

		if (timeFromLastDamage.getElapsedTime().asSeconds() >= DAMAGE_RECOVERY_RATE && is_Player_In_Zone_For_Attack && !is_Game_Paused && !is_Inventory_Opened) {
			damageTakenbyPlayer(0.05f, HPLevel, spriteSize, player.playersprite, timeFromLastDamage, damagePlayer.sound);
			if (timeFromLastDamage.getElapsedTime().asSeconds() > DAMAGE_RECOVERY_RATE + 1) {
				timeFromLastDamage.restart();
			}
		}

		if (timeFromLastDamage.getElapsedTime().asSeconds() > HP_RECOVERY_TIME && !is_Game_Paused && !is_Inventory_Opened) {
			HPLevel += HP_RECOVERY_RATE;
			if (HPLevel >= 1.f) {
				HPLevel = 1.f;
			}
		}

		//timers with time limit



		changeview();
		window.setView(view);

		GAME_Version_Information.setPosition(view.getCenter().x - 310, view.getCenter().y + 420);
		window.draw(GAME_Version_Information);

		if (!is_Inventory_Opened && !is_Game_Paused) {
			Kafer.checkDistanceForAttack(player.playersprite, is_Player_In_Zone_For_Attack);
			Kafer.update(timenpc, dir, player.playersprite, Kafer.npc_sprite, HPLevel, spriteSize, timeFromLastDamage);
			window.draw(Kafer.npc_sprite);
			window.draw(player.playersprite);
			window.draw(GUN_Pistol_ICON.itemsprite);
			Indicatorcalc(Indicators.playerpropsprite, window, energyLevel, indicatorsPosX, indicatorsPosY, HPLevel, indicatorsHPPosY,
				is_Player_Can_Run, playerSpeedNormal, playerSpeedRunning);
			Indicators.playerpropsprite.setPosition(indicatorSpritePosX, indicatorSpritePosY);
			window.draw(Indicators.playerpropsprite);
			player.update(times);
			viewmap(times);
		}
	
		 
		window.display();

	}

	return 0;
}