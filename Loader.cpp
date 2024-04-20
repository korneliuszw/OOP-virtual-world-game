//
// Created by kwojn on 4/20/2024.
//

#include <fstream>
#include "Loader.h"
#include "Zwierzeta.h"
#include "Rosliny.h"
#include "Player.h"

void Loader::save() {
    std::ofstream file;
    file.open("save.txt");
    file << swiat.getWidth() << " " << swiat.getHeight() << std::endl;
    for (auto &entries: swiat.mapper) {
        for (auto &organism: entries.second)
            organism->serialize(file);
    }
    file.close();
}

void Loader::load(WindowManager *windowManager) {
    std::ifstream file;
    file.open("save.txt");
    int width, height;
    file >> width >> height;
    this->swiat = Swiat(width, height);
    char organismType;
    file >> std::skipws;
    while (file >> organismType) {
        std::shared_ptr<Organizm> organism;
        if (organismType == 'Z') {
            organism = Zwierzeta::deserialize(file);
        } else if (organismType == 'R') {
            organism = Rosliny::deserialize(file);
        } else if (organismType == 'P')
            organism = Player::deserialize(file, windowManager);
        else
            throw std::runtime_error("Unknown organism type");
        if (organism)
            this->swiat.spawn(organism, true);
    }
    file.close();
}


