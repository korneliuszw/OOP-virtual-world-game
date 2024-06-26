//
// Created by kwojn on 4/6/2024.
//

#ifndef PROJEKT1_WINDOWMANAGER_H
#define PROJEKT1_WINDOWMANAGER_H

#include <ncurses.h>
#include "ScrollableList.h"
#include "Loader.h"

class WindowManager {
    WINDOW *screen;
    WINDOW *mainGameWindow;
    WINDOW *bottomWindow;
    ScrollableList scrollableList;
    Loader &loader;
    std::string statusText;
public:
    void setStatusText(const std::string &statusText);

public:
    ScrollableList &getScrollableList();

public:
    WINDOW *getMainGameWindow() const;

    WINDOW *getBottomWindow() const;

private:
    WINDOW *createWindow(int x, int y, int w, int h);

public:
    WindowManager(int gameWidth, int gameHeight, Loader &loader);

    ~WindowManager();

    bool handleWindowControls(int key);

    void draw();

    void clear();
};


#endif //PROJEKT1_WINDOWMANAGER_H
