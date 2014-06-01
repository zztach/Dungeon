/* 
 * File:   ListBox.h
 * Author: zisis
 *
 * Created on April 21, 2014, 8:48 PM
 */

#ifndef LISTBOX_H
#define	LISTBOX_H

#include <vector>
#include "Control.h"
using std::vector;
 
class ListBox : public Control 
{
public:
    ListBox(int positionX, int positionY, int w, int h);
    
    void addItem(string item);
    void removeItem(int index);
    void setCurrent(int index);
    int getIndex() const;
    int getCount() const;
    virtual bool update(MouseState& state);
    virtual string getType(void) const;
    virtual void bindVAO(); 
    virtual void render(const GLuint program, const double timeElapsed);
    
    virtual ~ListBox();    
protected:
    int                 index;
    vector<string>      items;

private:
    GLuint buffer;
    GLuint vao;
    TextRenderer* textRenderer;

};

#endif	/* LISTBOX_H */

