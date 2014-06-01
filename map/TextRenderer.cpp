/* 
 * File:   TextRenderer.cpp
 * Author: zisis
 * 
 * Created on March 31, 2014, 11:25 PM
 */

#include "TextRenderer.h"
#include "ShaderUniform.h"

const float fontSize = 26.0f;
const float size = 16.0f;
const int fontSpace = 14.0f;

TextRenderer::TextRenderer(GLuint fontTexture) {
    this->fontTexture = fontTexture;
}

TextRenderer::~TextRenderer() {
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &vao);
}


void TextRenderer::bindVAO() {    
    glGenVertexArrays(1, &vao); // Create our Vertex Array Object  
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it  
    //each letter utilizes 16 positions on the array    

    GLfloat* vertex_positions_2 = new GLfloat[256*20];
    for (int i = 0; i < 256; i++) {
        float cx = (float) (i % 16) / 16.0f;
        float cy = (float) (i / 16) / 16.0f;
        
        int offset = i * 20;
        
        vertex_positions_2[offset] = 0;
        vertex_positions_2[offset+1] = fontSize;
        vertex_positions_2[offset+2] = 0.0f;        
        vertex_positions_2[offset+3] = cx;
        vertex_positions_2[offset+4] = 1.0f - cy - 0.0625f;

        vertex_positions_2[offset+5] = fontSize;
        vertex_positions_2[offset+6] = fontSize;
        vertex_positions_2[offset+7] = 0.0f;        
        vertex_positions_2[offset+8] = cx + 0.0625f;
        vertex_positions_2[offset+9] = 1.0f - cy - 0.0625f;

        vertex_positions_2[offset+10] = fontSize;
        vertex_positions_2[offset+11] = 0.0f;
        vertex_positions_2[offset+12] = 0.0f;        
        vertex_positions_2[offset+13] = cx + 0.0625f;
        vertex_positions_2[offset+14] = 1.0f - cy;

        vertex_positions_2[offset+15] = 0.0f;
        vertex_positions_2[offset+16] = 0.0f;
        vertex_positions_2[offset+17] = 0.0f;
        vertex_positions_2[offset+18] = cx;
        vertex_positions_2[offset+19] = 1.0f - cy;      
        
    }
     // load vertex positions into the buffer, input to vertex attributes 0,3
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat)*256*20, vertex_positions_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    
    glBindVertexArray(0);
 
    delete vertex_positions_2;    
}
void TextRenderer::render(const GLuint program, GLint x, GLint y, std::string text) {    
    glDisable(GL_CULL_FACE);    
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    
    GLuint mv_location = ShaderUniform::getInstance(program)->get("mv_matrix");
    glBindVertexArray(vao);
    GLfloat colora[] = {1.0f, 0.0f, 0.0f, 1.0f};    
    glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(float(x), float(y), 0.0));
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    glVertexAttrib4fv(2, colora);
    
    for (int i=0; i<text.length(); i++) {
        glDrawArrays(GL_TRIANGLE_FAN, (text.at(i))*4 -32*4, 4);
        glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(fontSpace*(i+1), 0.0, 0.0));
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    }    
    glDisable(GL_BLEND);
}

