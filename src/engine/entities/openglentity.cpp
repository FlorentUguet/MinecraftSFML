#include "openglentity.h"

#include "../textures/opengltexture.h"
#include "../textures/opengltextureatlas.h"
#include "../scene.h"

#include "openglattribute.h"

OpenGLEntity::OpenGLEntity(OpenGLEntity *parent)
{
    setParent(parent);
    this->loaded = false;
}

OpenGLEntity::~OpenGLEntity()
{
    for(int i=this->children.size()-1;i>=0;i--)
    {
        delete this->children[i];
    }

    this->clearBuffers();
}

void OpenGLEntity::clearBuffers()
{
    glDeleteBuffers(1, &this->vboIndices);
    glDeleteVertexArrays(1,&this->vao);
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
    this->verticesXYZ.push_back(x);
    this->verticesXYZ.push_back(y);
    this->verticesXYZ.push_back(z);

    this->verticesCount++;
}

void OpenGLEntity::addTexCoord(GLfloat u, GLfloat v)
{
    this->verticesUV.push_back(u);
    this->verticesUV.push_back(v);
}

void OpenGLEntity::addIndice(GLuint i)
{
    this->verticesI.push_back(i);
}

void OpenGLEntity::setTexture(OpenGLTexture *texture)
{
    this->texture = texture;
}

void OpenGLEntity::setTextureAtlas(OpenGLTextureAtlas *atlas)
{
    this->clearBuffers();
    this->atlas = atlas;
    this->setTexture(atlas->getTexture());

    //this->textureCoordinates = this->atlas->convertUVs(this->textureCoordinates,)

    this->loadBuffer();
}

void OpenGLEntity::loadBuffer()
{
    this->clearBuffers();

    if(this->verticesXYZ.size() != 0)
    {
        //Vertices
        if(this->verticesXYZ.size() != 0)
        {
            GLfloat data[this->verticesXYZ.size()];
            std::copy(this->verticesXYZ.begin(),this->verticesXYZ.end(),data);
            this->attributes.push_back(new OpenGLAttribute(0, data, sizeof(data), 3, GL_FLOAT, GL_FALSE, 0));
            GLUtils::OutputErrors("OpenGLEntity->loadBuffer(VBO)");
        }

        //Texture
        if(this->verticesUV.size() != 0)
        {
            GLfloat data[this->verticesUV.size()];
            std::copy(this->verticesUV.begin(),this->verticesUV.end(),data);
            this->attributes.push_back(new OpenGLAttribute(1, data, sizeof(data), 2, GL_FLOAT, GL_FALSE, 0));
            GLUtils::OutputErrors("OpenGLEntity->loadBuffer(VBO Texture)");
        }

        //Indexes
        if(this->verticesI.size() != 0)
        {
            GLuint data[this->verticesI.size()];
            std::copy(this->verticesI.begin(),this->verticesI.end(),data);

            glGenBuffers(1, &this->vboIndices);
            glBindBuffer(GL_ARRAY_BUFFER, this->vboIndices);
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

            GLUtils::OutputErrors("OpenGLEntity->loadBuffer(Indices)");
        }

        updateVAO();
        this->loaded = true;

        GLUtils::OutputErrors("OpenGLEntity->loadBuffer(VAO)");
    }
}

void OpenGLEntity::updateVAO()
{
    if(this->vao == 0)
        glDeleteBuffers(1,&this->vao);

    //VAO
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    for(unsigned i=0;i<this->attributes.size();i++)
    {
        OpenGLAttribute *a = this->attributes[i];
        a->attach();
    }

    glBindVertexArray(0);
}

OpenGLAttribute *OpenGLEntity::getAttribute(GLuint index)
{
    OpenGLAttribute  *a = 0;

    for(unsigned i=0;i<this->attributes.size();i++)
    {
        if(this->attributes[i]->getIndex() == index)
            a = this->attributes[i];
    }

    return a;
}

void OpenGLEntity::setInstances(std::vector<glm::vec3> instances)
{
    this->instances = instances;
    glm::vec3 data[this->instances.size()];
    std::copy(this->instances.begin(), this->instances.end(), data);

    OpenGLAttribute *a = this->getAttribute(2);

    if(a == 0)
    {
        a = new OpenGLAttribute(2, &data[0], sizeof(glm::vec3) * instances.size(), 3, GL_FLOAT, GL_FALSE, 0);
        a->setAttribDivisor(1);
        this->attributes.push_back(a);
    }
    else
    {
        a->generate(data, sizeof(data));
    }

    this->updateVAO();
}

void OpenGLEntity::translate(float x, float y, float z)
{
    this->translate(glm::vec3(x,y,z));
}

void OpenGLEntity::translate(glm::vec3 pos)
{
    this->translation = pos;
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

glm::mat4 OpenGLEntity::getMVP(Scene *scene)
{
    return scene->calculateMVP(this);
}

void OpenGLEntity::draw(Scene *scene)
{
    glm::mat4 mvp = this->getMVP(scene);
    glUniformMatrix4fv(scene->getMVPId(), 1, GL_FALSE, &mvp[0][0]);

    if(this->loaded)
    {
        if(this->texture != 0)
            glBindTexture(GL_TEXTURE_2D,this->texture->getId());

        glBindVertexArray(this->vao);

        if(this->getAttribute(2) != 0)
        {
            OpenGLAttribute *a = this->getAttribute(2);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vboIndices);
            glDrawElementsInstanced(GL_TRIANGLES, this->verticesI.size(), GL_UNSIGNED_INT, 0, a->getLength());
        }
        else if(this->vboIndices != 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vboIndices);
            glDrawElements(GL_TRIANGLES, this->verticesI.size(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        }

        glBindVertexArray(0);
    }

    for(int i=0;i<this->children.size();i++)
    {
        if(this->children[i]->isVisible())
            this->children[i]->draw(scene);
    }
}

void OpenGLEntity::updateDirectionCulling(OpenGLEntity *reference)
{

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

GLuint OpenGLEntity::getVAO()
{
    return this->vao;
}

GLuint OpenGLEntity::getVBOIndices()
{
    return this->vboIndices;
}

OpenGLTexture* OpenGLEntity::getTexture()
{
    return this->texture;
}

int OpenGLEntity::getVerticesIndexesCount()
{
    return this->verticesI.size();
}
