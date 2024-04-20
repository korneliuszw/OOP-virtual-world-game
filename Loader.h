//
// Created by kwojn on 4/20/2024.
//

#include <stdexcept>
#include "WindowManager.h"

#ifndef PROJEKT1_LOADER_H
#define PROJEKT1_LOADER_H

class WindowManager;
class Swiat;

class Loader {
    Swiat &swiat;
public:
    void load(WindowManager *windowManager);

    void save();

    explicit Loader(Swiat &swiat) : swiat(swiat) {}


};

class Serializable {
    friend class Loader;

protected:
    virtual void serialize(std::ofstream &file) {
        throw std::runtime_error("Not implemented");
    };

};


#endif //PROJEKT1_LOADER_H