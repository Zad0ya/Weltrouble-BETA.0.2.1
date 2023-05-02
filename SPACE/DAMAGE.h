
void damageTakenbyPlayer(float damage, float& HPLevel, sf::FloatRect spriteSize, sf::Sprite& player, sf::Clock& timeFromLastDamage,
    sf::Sound& damagePlayer) {
    if (spriteSize.width * 0.5f - 114 - 1 * (1 - HPLevel) <= 0) {
    }
    else {
        HPLevel -= damage;
        if (timeFromLastDamage.getElapsedTime().asSeconds() < 2.5f) {
            sf::Color redColor = sf::Color(255, 0, 0);
            player.setColor(redColor);
            damagePlayer.play();
        }
        else {
            player.setColor(sf::Color::White);
        }
        float initialRotation = player.getRotation();
        if (timeFromLastDamage.getElapsedTime().asSeconds() < 2.1f) {
            player.setRotation(initialRotation + 4.f);
        }
        else if (timeFromLastDamage.getElapsedTime().asSeconds() > 2.2f && 
            2.3f < timeFromLastDamage.getElapsedTime().asSeconds()) {
            player.setRotation(initialRotation);
        }
        else if (timeFromLastDamage.getElapsedTime().asSeconds() > 2.4f &&
            2.5f < timeFromLastDamage.getElapsedTime().asSeconds()) {
            player.setRotation(initialRotation - 4.f);
        }
        else {
            player.setRotation(initialRotation);
        }
        
    }
}




void deathAnimation(sf::Sprite player) {
}
