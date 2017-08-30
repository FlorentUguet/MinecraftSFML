#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "json/json.h"
#include <iostream>
#include <fstream>

class JsonUtils
{
public:
    static Json::Value ReadFromFile(std::string file);
};



#endif // JSONUTILS_H
