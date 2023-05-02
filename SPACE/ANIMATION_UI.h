#ifndef ANIMATION_UI_HPP
#define ANIMATION_UI_HPP


void animatePanel_LEFT_TOP(sf::RenderWindow& window, sf::Sprite& Menubar, sf::Text& Font_Main2, const std::string& text) {
    Menubar.setTextureRect(sf::IntRect(176, 65, 851, 400));
    Menubar.setPosition(-Menubar.getGlobalBounds().width, 10);
    sf::RectangleShape rect(sf::Vector2f(window.getSize().x, window.getSize().y));
    rect.setFillColor(sf::Color(0, 0, 0, 0)); 

    sf::Clock animatepanel;
    for (int i = -Menubar.getGlobalBounds().width; i <= 0; i += 5) {
       
        window.draw(rect);
        Menubar.setPosition(i, 0.f);
        Font_Main2.setPosition(Menubar.getPosition().x + 70.f, Menubar.getPosition().y + 30.f);
        Font_Main2.setString(text);
        window.draw(Menubar);
        window.draw(Font_Main2);
        window.display();
        animatepanel.restart();
        while (animatepanel.getElapsedTime().asMilliseconds() < 20) {
        }
        window.clear();

    }
    if (Menubar.getPosition().x == 0) {
        Menubar.setPosition(0.f, 0.f);
        Font_Main2.setPosition(Menubar.getPosition().x + 70.f, Menubar.getPosition().y + 30.f);
        window.draw(Menubar);
        window.draw(Font_Main2);
        window.display();
        sf::Clock animatepanel2;
        while (animatepanel2.getElapsedTime().asMilliseconds() < 300) {
        }
    }
}


#endif // ANIMATION_UI_HPP