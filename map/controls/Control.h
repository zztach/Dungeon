/* 
 * File:   Control.h
 * Author: zisis
 *
 * Created on April 21, 2014, 7:29 PM
 */

#ifndef CONTROL_H
#define	CONTROL_H

#include <list>
#include <string>
#include "../IDrawable.h"
#include "../utils/ShaderUniform.h"
#include "../TextRenderer.h"

using std::list;
using std::string;

struct MouseState
{
    int leftButtonDown;
    int rightButtonDown;
    int middleButtonDown;
    
    int x,y;
    
    MouseState()
    {
        leftButtonDown = 0;
        rightButtonDown = 0;
        middleButtonDown = 0;
        
        x = 0;
        y = 0;
    }
};

class Control : public IDrawable {
public:
    static list<Control*> controls;
public:
    Control(int positionX, int positionY, int w, int h);   
    virtual ~Control();
    virtual bool update(MouseState& state);
    virtual string getType(void) const = 0;
    void setPosition(int x, int y);
    void setSize(int width, int height);
    const int getWidth() const;
    const int getHeight() const;
protected:
    bool        inside;
    int         posX, posY;
    int         width, height;

};

#endif	/* CONTROL_H */

