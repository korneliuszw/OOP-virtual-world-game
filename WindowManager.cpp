//
// Created by kwojn on 4/6/2024.
//

#include "WindowManager.h"
#include <cstdlib>
#include <cstddef>
#include <iostream>
using std::size_t;

WindowManager::WindowManager(int gameWidth, int gameHeight) {
    size_t screenHeight = getmaxy(stdscr);
    size_t screenWidth = getmaxx(stdscr);
    int bottomPaneHeight = 10;
    if (screenHeight - bottomPaneHeight < gameHeight || screenWidth < gameWidth) {
        std::cerr << "Current window can't fit the game";
        std::exit(1);
    }
    screen = initscr();
    clear();
    cbreak();
    noecho();
    nodelay(screen, TRUE);
    keypad(screen, TRUE);
    nonl();
    this->mainGameWindow = createWindow(0, 0, screenWidth, screenHeight - bottomPaneHeight);
    this->bottomWindow  = createWindow(0, screenHeight - bottomPaneHeight, screenWidth, bottomPaneHeight);
}

WINDOW *WindowManager::createWindow(int x, int y, int w, int h) {
    return newwin(h, w, y, x);
}

WindowManager::~WindowManager() {
    delwin(this->bottomWindow);
    delwin(this->mainGameWindow);
    delwin(this->screen);
}

void WindowManager::draw() {
    wrefresh(mainGameWindow);
    wrefresh(bottomWindow);
}

void WindowManager::clear() {
    wclear(mainGameWindow);
}

WINDOW *WindowManager::getMainGameWindow() const {
    return mainGameWindow;
}

WINDOW *WindowManager::getBottomWindow() const {
    return bottomWindow;
}

