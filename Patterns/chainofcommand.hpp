//
// Created by penguinrage on 24/07/17.
//

#ifndef DESIGN_PATTERNS_CHAINOFCOMMAND_HPP
#define DESIGN_PATTERNS_CHAINOFCOMMAND_HPP

#include <iostream>
#include <string>

class Photo {
public:
    Photo(std::string s) : mTitle(s) {
        std::cout << "Processing " << mTitle << " ...\n";
    }

private:
    std::string mTitle;
};

class PhotoProcessor {
public:
    PhotoProcessor() : mNextProcessor(0) {}

public:
    void process(Photo &p) {
        processImplementation(p);
        if (mNextProcessor != 0)
            mNextProcessor->process(p);
    }

    virtual ~PhotoProcessor() {}

    void setNextProcessor(PhotoProcessor *p) {
        mNextProcessor = p;
    }

protected:
    virtual void processImplementation(Photo &a) = 0;

private:
    PhotoProcessor *mNextProcessor;
};

class Scale : public PhotoProcessor {
public:
    enum SCALE {
        S50, S100, S200, S300, S500
    };

    Scale(SCALE s) : mSCALE(s) {}

private:
    void processImplementation(Photo &a) {
        std::cout << "Scaling photo\n";
    }

    SCALE mSCALE;
};

class RedEye : public PhotoProcessor {
private:
    void processImplementation(Photo &a) {
        std::cout << "Removing red eye\n";
    }
};

class Filter : public PhotoProcessor {
private:
    void processImplementation(Photo &a) {
        std::cout << "Applying filters\n";
    }
};

class ColorMatch : public PhotoProcessor {
private:
    void processImplementation(Photo &a) {
        std::cout << "Matching colors\n";
    }
};

void processPhoto(Photo &photo) {
    ColorMatch match;
    RedEye eye;
    Filter filter;
    Scale scale(Scale::S200);
    scale.setNextProcessor(&eye);
    eye.setNextProcessor(&match);
    match.setNextProcessor(&filter);
    scale.process(photo);
}

#endif //DESIGN_PATTERNS_CHAINOFCOMMAND_HPP
