#include <iostream>
#include <string>
#include <unordered_map>
#include <locale.h>

class LanguageGLOBAL {
public:
    LanguageGLOBAL() {}

    void setLanguage(std::string lang) {

        if (lang == "EN" || lang == "RU" || lang == "DE" || lang == "UA") {
            current_language_ = lang;
        }
        else {
            std::cerr << "Unsupported language. Defaulting to English." << std::endl;
            current_language_ = "EN";
        }
    }

    std::string getString(std::string key) {
        std::string lang_key = current_language_ + "_" + key;
        auto it = strings_.find(lang_key);
        if (it == strings_.end()) {
            std::cerr << "Key not found: " << lang_key << std::endl;
            return "";
        }
        return it->second;
    }
      void updateStrings() {
        for (auto& pair : strings_) {
            if (pair.first.substr(0, 2) == current_language_) {
                continue;
            }
            std::string lang_key = current_language_ + pair.first.substr(2);
            auto it = strings_.find(lang_key);
            if (it == strings_.end()) {
                std::cerr << "Key not found: " << lang_key << std::endl;
                continue;
            }
            pair.second = it->second;
        }
    }


private:
    std::string current_language_ = "EN";

    std::unordered_map<std::string, std::string> strings_ = {

        {"EN_MENU", "Continue;Statistics;Settings;Exit;"},
        {"RU_MENU", "Продовжити;Статистика;Налаштування;Вихід;"},
        {"DE_MENU",  "Weitermachen;Statistiken;Einstellungen;Aus;"},
        {"UA_MENU",  "Weitermachen;Statistiken;Einstellungen;Aus;"},

        {"EN_MENU_SETTINGS", "Language;Game Volume;Music Volume;Shader Quality;Number of objects;"},
        {"RU_MENU_SETTINGS", "Язык;Громкость игры;Громкость музыки;Качество шейдеров;Количество объектов;"},
        {"DE_MENU_SETTINGS", "Sprache;Spiellautstarke;Musiklautstarke;Shader-Qualitat;Anzahl von Objekten;"},
        {"UA_MENU_SETTINGS", "Мова;Гучність гри;Гучність музики;Якість шейдерів;Кількість об'єктів;"},

        {"EN_MENU_STAT", "Creatures killed:;Marks earned:;Marks spent:;Trust level:;"},
        {"RU_MENU_STAT", "Убито существ:;Марксов заработанно:;Марксов потрачено:;Уровень доверия:;"},
        {"DE_MENU_STAT", "Getötete Kreaturen:;Verdiente Marks:;Ausgegebene Marks:;Vertrauensstufe:;"},
        {"UA_MENU_STAT", "Вбито істот:; Марксов зароблено:; Марксов витрачено:; Рівень довіри:;"},

        {"EN_INVENTORY_DROPPED", "You have \n dropped an item!"},
        {"RU_INVENTORY_DROPPED", "Вы выбросили предмет!"},
        {"DE_INVENTORY_DROPPED", "Du hast einen Gegenstand fallen lassen!"},
        {"UA_INVENTORY_DROPPED", "Ви викинули предмет!"},

        {"EN_INVENTORY_FULL", "Inventory is full!"},
        {"RU_INVENTORY_FULL", "Инвентарь полон!"},
        {"DE_INVENTORY_FULL", "Das Inventar ist voll!"},
        {"UA_INVENTORY_FULL", "Інвентар повний!"},

        {"EN_INVENTORY_ITEM_SELECTED", "You have \n selected an item!"},
        {"RU_INVENTORY_ITEM_SELECTED", "Вы выбрали предмет!"},
        {"DE_INVENTORY_ITEM_SELECTED", "You have \n dropped an item!"},
        {"UA_INVENTORY_ITEM_SELECTED", "Ви обрали предмет!"},

        {"EN_VOLUME_MAX", "You have \n selected an item!"},
        {"RU_VOLUME_MAX", "Вы выбрали предмет"},
        {"DE_VOLUME_MAX", "You have \n dropped an item!"},

        {"EN_VOLUME_MIN", "You have \n selected an item!"},
        {"RU_VOLUME_MIN", "Вы выбрали предмет"},
        {"DE_VOLUME_MIN", "You have \n dropped an item!"}

    
    };
};



