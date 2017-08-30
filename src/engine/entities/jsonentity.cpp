#include "jsonentity.h"

JsonEntity::JsonEntity(OpenGLEntity *parent) : OpenGLEntity(parent)
{

}

JsonEntity::JsonEntity(std::string file, OpenGLEntity *parent) : JsonEntity(parent)
{
    this->value = JsonUtils::ReadFromFile(file);
}

JsonEntity::JsonEntity(Json::Value value, OpenGLEntity *parent) : JsonEntity(parent)
{
    this->value = value;
}

void JsonEntity::init()
{
    if(this->value != Json::Value::null)
    {
        //Vertices
        if(this->value["vertices"].isArray())
        {
            for(int i=0;i<this->value["vertices"].size();i+=3)
            {
                this->addVertice(
                        this->value["vertices"][i].asFloat(),
                        this->value["vertices"][i+1].asFloat(),
                        this->value["vertices"][i+2].asFloat());
            }
        }

        //Texture UVs
        if(this->value["uvs"].isArray())
        {
            for(int i=0;i<this->value["uvs"].size();i+=2)
            {
                this->addTexCoord(
                        this->value["uvs"][i].asFloat(),
                        this->value["uvs"][i+1].asFloat());
            }
        }

        //Indexes
        if(this->value["indices"].isArray())
        {
            for(int i=0;i<this->value["indices"].size();i++)
            {
                this->addIndice(this->value["indices"][i].asUInt());
            }
        }

        this->loadBuffer();
    }
}
