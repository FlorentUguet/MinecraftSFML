#include "openglentity.h"

OpenGLEntity::OpenGLEntity(OpenGLEntity *parent)
{
    setParent(parent);
    this->loaded = false;
}

OpenGLEntity::~OpenGLEntity()
{
    glDeleteBuffers(1, &this->vbo);
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

void OpenGLEntity::addVertice(GLfloat x, GLfloat y, GLfloat z)
{
    this->vertices.push_back(x);
    this->vertices.push_back(y);
    this->vertices.push_back(z);
    this->verticesCount++;
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
}

void OpenGLEntity::translate(float x, float y, float z)
{
    this->translation = glm::vec3(x,y,z);
}

void OpenGLEntity::rotate(float x, float y, float z)
{
    this->rotation = glm::vec3(glm::radians(x),glm::radians(y),glm::radians(z));
}

glm::mat4 OpenGLEntity::getTransformedMatrix()
{
    glm::mat4 source = this->parent == 0 ? glm::mat4(1.0f) : this->parent->getTransformedMatrix();
    glm::mat4 scaled = glm::scale(source,glm::vec3(1.0f));

    glm::mat4 rotated = glm::rotate(scaled,this->rotation.x, glm::vec3(1,0,0));
    rotated = glm::rotate(scaled,this->rotation.y, glm::vec3(0,1,0));
    rotated = glm::rotate(scaled,this->rotation.z, glm::vec3(0,0,1));

    glm::mat4 translated = glm::translate(rotated,this->translation);
    return translated;
}

void OpenGLEntity::draw(Scene *scene)
{
    glm::mat4 mvp = scene->calculateMVP(this);
    glUniformMatrix4fv(scene->getMVPId(), 1, GL_FALSE, &mvp[0][0]);

    if(this->loaded)
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           VERTICE_SIZE,       // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glDisableVertexAttribArray(0);
    }

    for(int i=0;i<this->children.size();i++)
    {
        this->children[i]->isVisible();
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
