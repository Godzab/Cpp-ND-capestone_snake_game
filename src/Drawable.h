#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

class Drawable{
public:
    Drawable();
    Drawable(int y, int x, char c);

    // Getters and setters
    int getX() const;
    int getY() const;
    char getIcon() const;

protected:
    int y;
    int x;
    char icon;
};

#endif