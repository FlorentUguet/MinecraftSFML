#include "openglentity.h"

OpenGLEntity::OpenGLEntity(OpenGLEntity *parent)
{
    setParent(parent);
    this->loaded = false;
}

OpenGLEntity::~OpenGLEntity()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->vboTexture);
}

void OpenGLEntity::setParent(OpenGLEntity* parent)
{
    if(this->parent != 0)
        this->parent->removeChild(this);

    this->parent = parent;

    if(this->parent != 0)
        this->parent->addChild(this);
}

void OpenGLEntity::addChild(OpenGLEntity *e)
{
    this->children.push_back(e);
}

void OpenGLEntity::removeChild(OpenGLEntity *e)
{
    std::vector<OpenGLEntity *>::iterator it;
    it = std::find(this->children.begin(), this->children.end(), e);
    if ( it != this->children.end() )
       this->children.erase(it);
}

void OpenGLEntity::init()
{
    loadBuffer();
}

void OpenGLEntity::addVertice(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v)
{
    addVertice(x, y, z);
    addTexCoord(u,v);
}

void OpenGLEntity::addVertice(GLfloat x, GLfloat y, GLfloat z)
{
    this->vertices.push_back(x);
    this->vertices.push_back(y);
    this->vertices.push_back(z);

    this->verticesCount++;
}

void OpenGLEntity::addTexCoord(GLfloat u, GLfloat v)
{
    this->textureCoordinates.push_back(u);
    this->textureCoordinates.push_back(v);
}

void OpenGLEntity::setTexture(OpenGLTexture *texture)
{
    this->texture = texture;
}

void OpenGLEntity::loadBuffer()
{
    if(this->vertices.size() != 0)
    {
        GLfloat g_vertex_buffer_data[this->vertices.size()];
        std::copy(this->vertices.begin(),this->vertices.end(),g_vertex_buffer_data);

        glGenBuffers(1, &this->vbo);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        this->loaded = true;
    }

    if(this->textureCoordinates.size() != 0)
    {
        GLfloat g_vertex_buffer_data[this->textureCoordinates.size()];
        std::copy(this->textureCoordinates.begin(),this->textureCoordinates.end(),g_vertex_buffer_data);

        glGenBuffers(1, &this->vboTexture);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }
}

void OpenGLEntity::translate(float x, float y, float z)
{
    this->translation = glm::vec3(x,y,z);
}

void OpenGLEntity::rotate(float x, float y, float z)
{
    this->rotation = glm::vec3(glm::radians(x),glm::radians(y),glm::radians(z));
    //this->rotation = glm::vec3(x,y,z);
}

void OpenGLEntity::scale(float scale)
{
    this->scaleVec = glm::vec3(scale);
}

glm::mat4 OpenGLEntity::getTransformedMatrix()
{
    glm::mat4 scaled = glm::scale(glm::mat4(1.0f),this->scaleVec);

    glm::mat4 rotated = glm::rotate(glm::mat4(1.0f),this->rotation.x, glm::vec3(1,0,0));
    rotated = glm::rotate(rotated,this->rotation.y, glm::vec3(0,1,0));
    rotated = glm::rotate(rotated,this->rotation.z, glm::vec3(0,0,1));

    glm::mat4 source = this->parent == 0 ? glm::mat4(1.0f) : this->parent->getTransformedMatrix();
    glm::mat4 translated = glm::translate(source,this->translation);

    glm::mat4 final = translated * rotated * scaled;
    return final;
}

void OpenGLEntity::draw(Scene *scene)
{
    glm::mat4 mvp = scene->calculateMVP(this);
    glUniformMatrix4fv(scene->getMVPId(), 1, GL_FALSE, &mvp[0][0]);

    if(this->loaded)
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        //Vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           VERTICE_SIZE,       // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        if(this->vboTexture > 0)
        {
            //glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,this->texture->getId());
            //Texture
            glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
            glVertexAttribPointer(
               1,
               TEXTURE_COORD_SIZE, // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               0,                  // stride
               (void*)0            // array buffer offset
            );
        }

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        glBindBuffer(GL_ARRAY_BUFFER,0);

        //Disable the attributes
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }

    for(int i=0;i<this->children.size();i++)
    {
        if(this->children[i]->isVisible())
            this->children[i]->draw(scene);
    }
}

void OpenGLEntity::hide()
{
    setVisible(false);
}

void OpenGLEntity::show()
{
    setVisible(true);
}

void OpenGLEntity::setVisible(bool visible)
{
    this->visible = visible;
}

bool OpenGLEntity::isVisible()
{
    return this->visible;
}
