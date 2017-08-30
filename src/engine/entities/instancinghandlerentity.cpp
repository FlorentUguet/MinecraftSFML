#include "instancinghandlerentity.h"
#include "../scene.h"
#include "../textures/opengltexture.h"
#include <glm/gtc/type_ptr.hpp>

InstancingHandlerEntity::InstancingHandlerEntity(OpenGLEntity *parent) : OpenGLEntity(parent)
{

}

void InstancingHandlerEntity::setSource(OpenGLEntity *e)
{
    this->source = e;
}


void InstancingHandlerEntity::setOffsets(std::vector<glm::vec3> offsets)
{
    if(this->vboOffsets != 0)
        glDeleteBuffers(1, &this->vboOffsets);

    this->offsets = offsets;

    glm::vec3 data[this->offsets.size()];

    std::copy(this->offsets.begin(), this->offsets.end(), data);

    glGenBuffers(1, &this->vboOffsets);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboOffsets);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->offsets.size(), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancingHandlerEntity::setShader(GLuint vertexShader)
{
    this->shader = vertexShader;
}

void InstancingHandlerEntity::draw(Scene *scene)
{
    glm::mat4 mvp = this->getMVP(scene);
    glUniformMatrix4fv(scene->getMVPId(), 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(this->source->getVAO());
    glBindTexture(GL_TEXTURE_2D,this->source->getTexture()->getId());

    //Instance Parameter
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboOffsets);
    GLUtils::OutputErrors("Bind Buffer");
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    GLUtils::OutputErrors("glVertexAttribPointer");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);


    glDrawElementsInstanced(GL_TRIANGLES,
                            this->source->getVerticesIndexesCount(),
                            GL_UNSIGNED_INT,
                            0,
                            this->offsets.size());

    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}
