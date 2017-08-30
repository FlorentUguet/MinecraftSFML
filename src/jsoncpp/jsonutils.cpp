#include "jsonutils.h"

Json::Value JsonUtils::ReadFromFile(std::string file)
{
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream test(file, std::ifstream::binary);

    bool parsingSuccessful = reader.parse( test, root, false );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << reader.getFormatedErrorMessages()
               << "\n";
        root = Json::Value::null;
    }

    return root;
}
