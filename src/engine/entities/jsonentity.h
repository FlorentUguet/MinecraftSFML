#ifndef JSONENTITY_H
#define JSONENTITY_H

#include "jsoncpp/jsonutils.h"

#include "openglentity.h"

class JsonEntity : public OpenGLEntity
{
public:
    JsonEntity(OpenGLEntity *parent = 0);
    JsonEntity(std::string file, OpenGLEntity *parent = 0);
    JsonEntity(Json::Value value, OpenGLEntity *parent = 0);

    void init();

private:
    Json::Value value;
};

#endif // JSONENTITY_H
