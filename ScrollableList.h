//
// Created by kwojn on 4/19/2024.
//

#ifndef PROJEKT1_SCROLLABLELIST_H
#define PROJEKT1_SCROLLABLELIST_H

#include <ncurses.h>
#include <list>
#include <string>

class ScrollableList {
    int visibleItems;
    std::list<std::string> items;
    int scrollOffset = 0;
    int topY;
public:
    ScrollableList(int visibleItems, int topY) : visibleItems(visibleItems), topY(topY) {}

    void draw(WINDOW *window);

    void scrollUp();

    void scrollDown();

    void append(const std::string &item);

    void reset();
};


#endif //PROJEKT1_SCROLLABLELIST_H
