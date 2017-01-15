/* 
 * File:   Control.cpp
 * Author: zisis
 * 
 * Created on April 21, 2014, 7:29 PM
 */

#include "Control.h"

list<Control*> Control::controls;

Control::Control(int positionX, int positionY, int w, int h) 
{
    this->controls.push_back(this);
    
    this->posX = positionX;
    this->posY = positionY;
    
    this->width = w;
    this->height = h;

}

bool Control::update(MouseState& state)
{
    int x = state.x;
    int y = state.y;
    
    inside = false;
    if (x >= posX && x <= posX + width
        && y >= posY && y <= posY + height)
    {
        inside = true;
    }
    
    return false;
}

string Control::getType(void) const
{
    
}

void Control::setPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void Control::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

const int Control::getWidth() const
{
    return width;
}

const int Control::getHeight() const
{
    return height;
}

Control::~Control() 
{
    controls.remove(this);

}

