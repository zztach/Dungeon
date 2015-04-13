/* 
 * File:   InputProcessor.h
 * Author: zisis
 *
 * Created on March 9, 2015, 1:28 AM
 */

#ifndef INPUTPROCESSOR_H
#define	INPUTPROCESSOR_H

#include <string>
#include <map>
#include "../controls/Control.h"
#include "InputState.h"
using std::string;
using std::map;

class InputProcessor
{
public:
    virtual ~InputProcessor() {};        
    virtual void process(map<char,KeyState*> keys, MouseState& mouseState, double frameTime) = 0;
};



#endif	/* INPUTPROCESSOR_H */

