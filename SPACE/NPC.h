#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cmath>


using namespace sf;


class NPCclassAnimal {
public:
    float x, y, w, h, dx, dy, speed = 0;
    int dir = 0, animFrame = 0, animDir = 1;
    String File;
    Image image;
    Texture texture;
    Sprite npc_sprite;
    NPCclassAnimal(String F, float X, float Y, float W, float H) {
        File = F;
        w = W; h = H;
        image.loadFromFile("images/mobs/" + File);
        if (!image.loadFromFile("images/mobs/" + File)) { std::cerr << ERRORMESSAG.toAnsiString() << "::::::" << File.toAnsiString() << std::endl; }
        else std::cout << "Item." << File.toAnsiString() << ".loaded;" << std::endl;
        image.createMaskFromColor(Color(237, 28, 36));
        texture.loadFromImage(image);
        npc_sprite.setTexture(texture);
        x = X; y = Y;
        npc_sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    sf::FloatRect getBoundingBox() {
        return npc_sprite.getGlobalBounds();
    }

    void checkDistanceForAttack(sf::Sprite player, bool& is_Player_In_Zone_For_Attack) {
        float distance = getDistanceToPlayer(npc_sprite.getPosition(), player.getPosition());
        if (distance < 85.0f) {
            is_Player_In_Zone_For_Attack = true;
        }
        else if (distance > 85.0f) {is_Player_In_Zone_For_Attack = false; }
    }

    bool intersects(const sf::FloatRect& r1, const sf::FloatRect& r2) {
        return r1.intersects(r2);
    }

    void update(float& timeNpc, int& dir, sf::Sprite player, sf::Sprite Kafer, float& HPLevel, sf::FloatRect spriteSize, sf::Clock& timeFromLastDamag) {
        animFrame += 0.160 * timeNpc;

        float distance = getDistanceToPlayer(Kafer.getPosition(), player.getPosition());

        if (distance < 340.0f) { 
            float angle = atan2(player.getPosition().y - Kafer.getPosition().y, player.getPosition().x - Kafer.getPosition().x);
            if (angle >= -pi4 && angle < pi4) {
                dir = 0;  
            }
            else if (angle >= pi4 && angle < 3 * pi4) {
                dir = 2; 
            }
            else if (angle >= -3 * pi4 && angle < -pi4) {
                dir = 3; 
            }
            else {
                dir = 1; 
            }
            switch (dir) {
            case 0: dx = speed; dy = 0;   break;
            case 1: dx = -speed; dy = 0;  break;
            case 2: dx = 0; dy = speed;   break;
            case 3: dx = 0; dy = -speed;  break;
            }
            x += dx * timeNpc;
            y += dy * timeNpc;
            npc_sprite.setPosition(x, y);
            animFrame += 0.160 * timeNpc;
            speed = 0.1;
        }
        else {
            switch (dir) {
            case 0: dx = speed; dy = 0;   break;
            case 1: dx = -speed; dy = 0;  break;
            case 2: dx = 0; dy = speed;   break;
            case 3: dx = 0; dy = -speed;  break;
            }
            x += dx * timeNpc;
            y += dy * timeNpc;
            speed = 0.02;
        }

  
        if (animFrame > 2) {
            animFrame = 0;
        }
        npc_sprite.setTextureRect(IntRect(animFrame * w, dir * h, w, h));
        npc_sprite.setPosition(x, y);
    }

    
    sf::Vector2f getPosition() const {
        return npc_sprite.getPosition();
    }

    float getDistanceToPlayer(sf::Vector2f npcPos, sf::Vector2f playerPos) {
        float dx = npcPos.x - playerPos.x;
        float dy = npcPos.y - playerPos.y;
        return std::sqrt(dx * dx + dy * dy);

    }
private:

    const float DAMAGE_RECOVERY_TIME = 2.0f;
    const double pi4 = std::atan(1.0);
    bool PLAYER_IN_ZONE = false;
};



