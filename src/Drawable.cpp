#include "Drawable.h"

Drawable::Drawable(){
    y = 0;
    x = 0;
    icon = ' ';
}

Drawable::Drawable(int y, int x, char c): y(y), x(x), icon(c){}

int Drawable::getX(){
    return x;
}
int Drawable::getY(){
    return y;
}
char Drawable::getIcon(){
    return icon;
}