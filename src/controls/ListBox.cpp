/* 
 * File:   ListBox.cpp
 * Author: zisis
 * 
 * Created on April 21, 2014, 8:48 PM
 */

#include <glew.h>

#include "ListBox.h"

const int itemHeight = 18;

ListBox::ListBox(int positionX, int positionY, int w, int h)
: Control(positionX, positionY, w, h)
{
    index = 0;
}

void ListBox::addItem(string item)
{
    items.push_back(item);
}

void ListBox::removeItem(int index)
{
    int i=0;
    for(vector<string>::iterator it = items.begin(); it != items.end(); it++)
    {
        if (i == index)
        {
            items.erase(it);
            break;
        }
        i++;
    }
    
    if (index >= (int)items.size()) {
        index = (int)items.size() - 1;
    }
}

void ListBox::setCurrent(int index)
{
    this->index = index;
}

int ListBox::getIndex() const
{
    return index;
}

int ListBox::getCount() const
{
    return (int)items.size();
}

bool ListBox::update(MouseState& state)
{
    Control::update(state);
    
    int x = state.x;
    int y = state.y;
    
    if (inside && state.leftButtonDown)
    {
        int tmpIndex = (y-posY) / itemHeight;
        
        if ((tmpIndex >= 0) && tmpIndex < (int) items.size())
        {
            index = tmpIndex;
            return true;
        }
    }
    
    return false;
}

void ListBox::bindVAO() {
    glGenVertexArrays(1, &vao); // Create our Vertex Array Object
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it

    static const GLint vertex_positions[] = {
        posX + width,   posY,
        posX        ,   posY,
        posX        ,   posY + height,
        posX + width,   posY + height,
        posX + width,   posY
    };   

    // load vertex positions into the buffer, input to vertex attributes 0,3
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void ListBox::render(const GLuint program, const double timeElapsed)
{        
    glDisable(GL_CULL_FACE);   
    glEnable(GL_BLEND);    
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);  
//    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);      
    GLuint mv_location = ShaderUniform::getInstance(program)->get("mv_matrix");
    glBindVertexArray(vao);
    
    //if (inside) 
    //{
        GLfloat colora[] = {1.0f, 0.6f, 0.6f, 0.3f};
        glVertexAttrib4fv(3, colora);
        glLineWidth(3.0f);
        std::cout << " INSIDE HERE L";
    //} 
//    else 
//    {
//        GLfloat colora[] = {1.0f, 0.2f, 0.7f, 0.5f};
//        glVertexAttrib4fv(3, colora);
//        glLineWidth(1.0f);
//        std::cout << " INSIDE HERE 2";
//    }    
    glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(float(posX), float(posY), 0.0));
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
    glDisable(GL_BLEND);
}

string ListBox::getType(void) const
{
    return "ListBox";
}


ListBox::~ListBox()
{
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &vao);
}
