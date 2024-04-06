#pragma once

#include <ostream>

class Serializable {
    virtual void serialize(std::ostream& out) = 0;
    virtual void deserialize(std::istream& in) = 0;

    friend std::ostream&  operator<<(std::ostream& out) {
        this->serialize(out);
        return out;
    }

    friend std::ostream& operator>>(std::istream& in) {
        this->deserialize(in);
        return in;
    }
}