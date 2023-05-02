#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>


void DrawPauseMenu(sf::RenderWindow& window, sf::View& viewinv, sf::RectangleShape& rect, sf::Sprite Menubar, sf::Text& Font_Main,
    sf::Vector2i mousePos, sf::Vector2f mousePosView, bool& Is_Game_Paused, sf::Sprite Menubar_Selection, bool& Is_Stat_Open, bool& Is_Settings_Open,
    sf::Sprite Menubar_BIG, sf::Sprite Menubar_BOX, int gameMusic, int gameVolume, LanguageGLOBAL menu, bool& settingsUpdate_bool) {
    
    int menubarsSum = 4;
    int xOffset_Menu = (window.getSize().x / 2.6 + 6);
    int yOffset_Menu = (200);
    int xOffset_Language = Menubar_BIG.getGlobalBounds().width / 2.7;
    int yOffset_Language = Menubar_BIG.getGlobalBounds().height / 4 + 80;
    int xOffset_Volume = Menubar_BIG.getGlobalBounds().width;
    int yOffset_Volume = Menubar_BIG.getGlobalBounds().height / 2.35;
    int temp = 0;

    bool buttonPressed = false;
    
    float tempVolume = 0;
    const float MENU_ICON_SizeX = 789;
    const float MENU_ICON_SizeY = 379;
    const float BUTTON_VOLUME_SizeX = 57;
    const float BUTTON_VOLUME_SizeY = 64;
    const float SETTINGS_LANGUAGE_BUTTTON_SizeX = 190;
    const float SETTINGS_LANGUAGE_BUTTTON_SizeY = 64;

    std::string tempLanguageMenuBuffer;
    std::string menuLanguageBuffer = menu.getString("MENU");
    std::string settingsLanguageBuffer = menu.getString("MENU_SETTINGS");
    std::string statLanguageBuffer = menu.getString("MENU_STAT");
    std::string languageChoise = "English;Russian;Ukraine;Deutsch;";


    sf::RectangleShape rectLang(sf::Vector2f(SETTINGS_LANGUAGE_BUTTTON_SizeX, SETTINGS_LANGUAGE_BUTTTON_SizeY));
    sf::RectangleShape rectVolume(sf::Vector2f(12, 48));

    Menubar_Selection.setTextureRect(IntRect(170, 43, 857, 433));
    Menubar_BIG.setPosition(window.getSize().x / 2 - Menubar_BIG.getGlobalBounds().width / 2, window.getSize().y / 2 - Menubar_BIG.getGlobalBounds().height / 2);

    window.setView(viewinv);
    rect.setFillColor(sf::Color(0, 0, 0, 70));
    window.draw(rect);
    Menubar.setTextureRect(IntRect(170, 43, 857, 433));

    if (Is_Settings_Open) {

        window.draw(Menubar_BIG);
        for (int l = 0; l < settingsLanguageBuffer.size(); l++) {
            if (settingsLanguageBuffer[l] == ';') {
                temp++;
                tempLanguageMenuBuffer = settingsLanguageBuffer.substr(0, l);
                Font_Main.setString(tempLanguageMenuBuffer);
                Font_Main.setPosition(Menubar_BIG.getGlobalBounds().width/4.7, Menubar_BIG.getGlobalBounds().height/4 + (97 * temp)); 
                window.draw(Font_Main);
                settingsLanguageBuffer.erase(0, l + 1);
                tempLanguageMenuBuffer.clear();
                l = 0;
            }
        }

        for (int i = menubarsSum; i > 0; i--) {
            Menubar_BOX.setTextureRect(IntRect(213, 43, SETTINGS_LANGUAGE_BUTTTON_SizeX, SETTINGS_LANGUAGE_BUTTTON_SizeY));
            Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 2.7 + ((Menubar_BOX.getGlobalBounds().width + 20) * i), Menubar_BIG.getGlobalBounds().height / 4 + 80);
            window.draw(Menubar_BOX);
            Font_Main.setString(languageChoise);
            for (int j = 0; j < languageChoise.size(); j++) {
                if (languageChoise[j] == ';') {
                    Font_Main.setString(languageChoise.substr(0, j));
                    Font_Main.setPosition(Menubar_BIG.getGlobalBounds().width / 2.7 + (((Menubar_BOX.getGlobalBounds().width + 20) * i)+10), Menubar_BIG.getGlobalBounds().height / 4 + 97);
                    window.draw(Font_Main);
                    languageChoise.erase(0, j + 1);
                    j = 0;
                    break;
                }
            }
        }
        for (int i = 1; i <= menubarsSum; i++) {
            sf::Vector2f menuButtonPos = sf::Vector2f(xOffset_Language + ((Menubar_BOX.getGlobalBounds().width + 20) * i), yOffset_Language);
            if (mousePosView.x >= menuButtonPos.x && mousePosView.x <= menuButtonPos.x + SETTINGS_LANGUAGE_BUTTTON_SizeX &&
                mousePosView.y >= menuButtonPos.y && mousePosView.y <= menuButtonPos.y + SETTINGS_LANGUAGE_BUTTTON_SizeY) {
                rectLang.setFillColor(sf::Color(255, 255, 255, 70));
                rectLang.setPosition(menuButtonPos.x, menuButtonPos.y);
                window.draw(rectLang);
                if (Mouse::isButtonPressed(Mouse::Left) && i == 1) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    saveSettings.seekg(0);
                    saveSettings << "DE" << std::endl;
                    saveSettings.close();
                    settingsUpdate_bool;
                    menu.updateStrings();

                }
                if (Mouse::isButtonPressed(Mouse::Left) && i == 2) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    saveSettings.seekg(0);
                    saveSettings << "UA" << std::endl;
                    saveSettings.close();
                    settingsUpdate_bool;
                    menu.updateStrings();
                }
                if (Mouse::isButtonPressed(Mouse::Left) && i == 3) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    saveSettings.seekg(0);
                    saveSettings << "RU" << std::endl;
                    saveSettings.close();
                    settingsUpdate_bool;
                    menu.updateStrings();

                }
                if (Mouse::isButtonPressed(Mouse::Left) && i == 4) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    saveSettings.seekg(0);
                    saveSettings << "EN" << std::endl;
                    saveSettings.close();
                    settingsUpdate_bool;
                    menu.updateStrings();

                }
            }
        }

        for (int i = 10; i > 0; i--) {
            if (i == 10) {
                Menubar_BOX.setTextureRect(IntRect(63, 203, 57, 64));
                Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.12, (Menubar_BIG.getGlobalBounds().height / 2.35));
                window.draw(Menubar_BOX);
            }
            if (i == 1) {
                Menubar_BOX.setTextureRect(IntRect(63, 325, 57, 64));
                Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.62, (Menubar_BIG.getGlobalBounds().height / 2.35));
                window.draw(Menubar_BOX);
            }
            Menubar_BOX.setTextureRect(IntRect(63, 45, 26, 59));
            Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.57 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 113 + Menubar_BOX.getGlobalBounds().height);
            window.draw(Menubar_BOX);
        }

        for (int i = 1; i <= 2; i++) {
            if (i == 1) { tempVolume = 1.12; }
            if (i == 2) { tempVolume = 1.62; }
            sf::Vector2f menuButtonVolumePos = sf::Vector2f(xOffset_Volume / tempVolume, yOffset_Volume);
            if (mousePosView.x >= menuButtonVolumePos.x && mousePosView.x <= menuButtonVolumePos.x + BUTTON_VOLUME_SizeX &&
                mousePosView.y >= menuButtonVolumePos.y && mousePosView.y <= menuButtonVolumePos.y + BUTTON_VOLUME_SizeY) {

                if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed) {
                    buttonPressed = true;
                }
                if (buttonPressed && !Mouse::isButtonPressed(Mouse::Left)) {
                    buttonPressed = false;
                }

                if (buttonPressed && i == 1) {
                        std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                        if (saveSettings.is_open()) {
                            std::string line1, line2, line3;
                            std::getline(saveSettings >> std::ws, line1); 
                            std::getline(saveSettings >> std::ws, line2); 
                            std::getline(saveSettings >> std::ws, line3);
                            int value = std::stoi(line2);
                            value += 10; 
                            if (value > 100) {
                                value = 100; 
                            }
                            saveSettings.seekg(0); 
                            saveSettings << line1 << '\n'; 
                            saveSettings << value << '\n'; 
                            saveSettings << line3 << '\n';
                            saveSettings.close();
                            settingsUpdate_bool;
                        }
                }
                if (buttonPressed && i == 2) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    if (saveSettings.is_open()) {
                        std::string line1, line2, line3;
                        std::getline(saveSettings >> std::ws, line1);
                        std::getline(saveSettings >> std::ws, line2);
                        std::getline(saveSettings >> std::ws, line3);
                        int value = std::stoi(line2);
                        value -= 10;
                        if (value < 0) {
                            value = 0;
                        }
                        saveSettings.seekg(0);
                        saveSettings << line1 << '\n';
                        saveSettings << value << '\n';
                        saveSettings << line3 << '\n';
                        saveSettings.close();
                        settingsUpdate_bool = true;
                    }

                }
            }
       }
        //Отрисовка шкалі звука игрі 
        for (int i = 0; i < (gameVolume / 10); i++) {
            rectVolume.setFillColor(sf::Color(0, 125, 255, 255));
            rectVolume.setPosition(Menubar_BIG.getGlobalBounds().width / 1.505 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 118 + Menubar_BOX.getGlobalBounds().height);
            window.draw(rectVolume);
        }
        for (int i = gameVolume / 10; i < 10; i++) {
            rectVolume.setFillColor(sf::Color(128, 128, 128, 255));
            rectVolume.setPosition(Menubar_BIG.getGlobalBounds().width / 1.505 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 118 + Menubar_BOX.getGlobalBounds().height);
            window.draw(rectVolume);
        }
        //

        //--------------------MUSIC
        for (int i = 10; i > 0; i--) {
            if (i == 10) {
                Menubar_BOX.setTextureRect(IntRect(63, 203, 57, 64));
                Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.12, (Menubar_BIG.getGlobalBounds().height / 1.89));
                window.draw(Menubar_BOX);
            }
            if (i == 1) {
                Menubar_BOX.setTextureRect(IntRect(63, 325, 57, 64));
                Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.62, (Menubar_BIG.getGlobalBounds().height / 1.89));
                window.draw(Menubar_BOX);
            }
            Menubar_BOX.setTextureRect(IntRect(63, 45, 26, 59));
            Menubar_BOX.setPosition(Menubar_BIG.getGlobalBounds().width / 1.57 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 213 + Menubar_BOX.getGlobalBounds().height);
            window.draw(Menubar_BOX);
        }

        for (int i = 1; i <= 2; i++) {
            if (i == 1) { tempVolume = 1.12; }
            if (i == 2) { tempVolume = 1.62; }
            sf::Vector2f menuButtonVolumePos = sf::Vector2f(xOffset_Volume / tempVolume, yOffset_Volume+100);
            if (mousePosView.x >= menuButtonVolumePos.x && mousePosView.x <= menuButtonVolumePos.x + BUTTON_VOLUME_SizeX &&
                mousePosView.y >= menuButtonVolumePos.y && mousePosView.y <= menuButtonVolumePos.y + BUTTON_VOLUME_SizeY) {

                if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed) {
                    buttonPressed = true;
                }
                if (buttonPressed && !Mouse::isButtonPressed(Mouse::Left)) {
                    buttonPressed = false;
                }

                if (buttonPressed && i == 1) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    if (saveSettings.is_open()) {
                        std::string line1, line2, line3;
                        std::getline(saveSettings >> std::ws, line1);
                        std::getline(saveSettings >> std::ws, line2);
                        std::getline(saveSettings >> std::ws, line3);
                        int value = std::stoi(line3);
                        value += 10;
                        if (value > 100) {
                            value = 100;
                        }
                        saveSettings.seekg(0);
                        saveSettings << line1 << '\n';
                        saveSettings << line2 << '\n';
                        saveSettings << value << '\n';
                        saveSettings.close();
                        settingsUpdate_bool;
                    }
                }
                if (buttonPressed && i == 2) {
                    std::fstream saveSettings("saved/savedsettings.txt", std::ios::in | std::ios::out);
                    if (saveSettings.is_open()) {
                        std::string line1, line2, line3;
                        std::getline(saveSettings >> std::ws, line1);
                        std::getline(saveSettings >> std::ws, line2);
                        std::getline(saveSettings >> std::ws, line3);
                        int value = std::stoi(line3);
                        value -= 10;
                        if (value < 0) {
                            value = 0;
                        }
                        saveSettings.seekg(0);
                        saveSettings << line1 << '\n';
                        saveSettings << line2 << '\n';
                        saveSettings << value << '\n';
                        saveSettings.close();
                        settingsUpdate_bool = true;
                    }

                }
            }
        }
        //Отрисовка шкалі music игрі 
        for (int i = 0; i < (gameMusic / 10); i++) {
            rectVolume.setFillColor(sf::Color(0, 125, 255, 255));
            rectVolume.setPosition(Menubar_BIG.getGlobalBounds().width / 1.505 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 218 + Menubar_BOX.getGlobalBounds().height);
            window.draw(rectVolume);
        }
        for (int i = gameMusic / 10; i < 10; i++) {
            rectVolume.setFillColor(sf::Color(128, 128, 128, 255));
            rectVolume.setPosition(Menubar_BIG.getGlobalBounds().width / 1.505 + ((Menubar_BOX.getGlobalBounds().width + 10) * i), (Menubar_BIG.getGlobalBounds().height / 4) + 218 + Menubar_BOX.getGlobalBounds().height);
            window.draw(rectVolume);
        }
        //--------------------------------------
        if (Keyboard::isKeyPressed(Keyboard::BackSpace) || Keyboard::isKeyPressed(Keyboard::Escape)) {
            Is_Settings_Open = false;
        }
    }

    if (Is_Stat_Open) {

        window.draw(Menubar_BIG);
        for (int l = 0; l < statLanguageBuffer.size(); l++) {
            if (statLanguageBuffer[l] == ';') {
                temp++;
                tempLanguageMenuBuffer = statLanguageBuffer.substr(0, l);
                Font_Main.setString(tempLanguageMenuBuffer);
                Font_Main.setPosition(Menubar_BIG.getGlobalBounds().width / 4.7, Menubar_BIG.getGlobalBounds().height / 4 + (97 * temp)); //идея с выравниванием текста
                window.draw(Font_Main);
                statLanguageBuffer.erase(0, l + 1);
                tempLanguageMenuBuffer.clear();
                l = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::BackSpace) || Keyboard::isKeyPressed(Keyboard::Escape)) {
            Is_Stat_Open = false;
        }
    }

    else if (!Is_Stat_Open && !Is_Settings_Open) {

        for (int i = menubarsSum; i > 0; i--) {
            Menubar.setPosition(window.getSize().x / 2.6, (200 * i) - 80);
            window.draw(Menubar);
        }
  
        for (int l = 0; l < menuLanguageBuffer.size(); l++) {
            if (menuLanguageBuffer[l] == ';') {
                temp++;
                tempLanguageMenuBuffer = menuLanguageBuffer.substr(0, l);
                Font_Main.setString(tempLanguageMenuBuffer);
                Font_Main.setPosition(Menubar.getGlobalBounds().left + Menubar.getGlobalBounds().width / tempLanguageMenuBuffer.size() +15, (200 * temp)); //идея с выравниванием текста
                window.draw(Font_Main);
                menuLanguageBuffer.erase(0, l + 1);
                tempLanguageMenuBuffer.clear();
                l = 0;
            }
        }


        for (int i = 1; i <= menubarsSum; i++) {
            sf::Vector2f menuButtonPos = sf::Vector2f(xOffset_Menu, ((i * yOffset_Menu) - 80));
            if (mousePosView.x >= menuButtonPos.x && mousePosView.x <= menuButtonPos.x + MENU_ICON_SizeX / 2 &&
                mousePosView.y >= menuButtonPos.y && mousePosView.y <= menuButtonPos.y + MENU_ICON_SizeY / 2) {
                Menubar_Selection.setPosition(menuButtonPos.x - 6, menuButtonPos.y);
                window.draw(Menubar_Selection);
                

                if (Mouse::isButtonPressed(Mouse::Left) && i == 1) {
                    Is_Game_Paused = false;
                }

                if (Mouse::isButtonPressed(Mouse::Left) && i == 2) {
                    Is_Stat_Open = true;
                }
                if (Mouse::isButtonPressed(Mouse::Left) && i == 3) {
                    Is_Settings_Open = true;
                }

                if (Mouse::isButtonPressed(Mouse::Left) && i == 4) {
                    window.close();
                    break;   //добавить вы уверенны что хотите выйти? 
                }
            }
        }
    }
}
