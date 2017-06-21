#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>

namespace patterns {
// Complex objects such as RGB
class RGB
{
public:
    class Builder;

private:
    const int red;
    const int green;
    const int blue;

    RGB(int r, int g, int b) : red(r), green(g), blue(b){}

public:
    void print() {
        std::cout << "RGB value dump:" << std::endl;
        std::cout << "Red: " << red << std::endl;
        std::cout << "Green: " << green << std::endl;
        std::cout << "Blue: " << blue << std::endl;
    }
};

class RGB::Builder {
private:
    int red;
    int green;
    int blue;

public:
    // Default values
    static const constexpr int defaultRed = 0;
    static const constexpr int defaultGreen = 0;
    static const constexpr int defaultBlue = 0;

    // Create builder with default values
    Builder() : red( defaultRed ), green( defaultGreen ), blue( defaultBlue ){ }

    // Setting values on complex object and return builder self
    Builder& setRed( const int r ){ red = r; return *this; }
    Builder& setGreen( const int g ){ green = g; return *this; }
    Builder& setBlue( const int b ){ blue = b; return *this; }

    // Sets Black
    Builder& setBlack() {
        red = 0;
        green = 0;
        blue = 0;

        return *this;
    }

    // Sets White
    Builder& setWhite() {
        red = 255;
        green = 255;
        blue = 255;

        return *this;
    }

    // Produce desired RGB values
    RGB build() {
        return RGB(red,green,blue);
    }
};

}


#endif // BUILDER_H
