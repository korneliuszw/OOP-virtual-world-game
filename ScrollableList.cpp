//
// Created by kwojn on 4/19/2024.
//

#include "ScrollableList.h"


void ScrollableList::draw(WINDOW *window) {
    auto it = items.begin();
    std::advance(it, scrollOffset);
    for (int i = visibleItems - 1; i >= 0; i--) {
        if (i + scrollOffset >= items.size())
            continue;
        wmove(window, topY + i, 0);
        waddstr(window, it->c_str());
        it++;
    }
}

void ScrollableList::scrollUp() {
    if (visibleItems < items.size() - visibleItems)
        scrollOffset += 1;
}

void ScrollableList::scrollDown() {
    if (scrollOffset > 0)
        scrollOffset -= 1;
}

void ScrollableList::append(const std::string &item) {
    items.push_front(item);
}

void ScrollableList::reset() {
    items.clear();
    scrollOffset = 0;
}
