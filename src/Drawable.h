#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

class Drawable{
public:
    Drawable();
    Drawable(int y, int x, char c);

    // Getters and setters
    int getX();
    int getY();
    char getIcon();

protected:
    int y;
    int x;
    char icon;
};

#endif