#include "json.h"


//extern int testJSONParser();




int main(){
    JSON * json = JSON::fromFile("input.json");
    if( json != nullptr)std::cout<< json->toString(true);
    JSON * leaf = json->path(".mysql.admin.group[0].username");
    if(leaf != nullptr) std::cout<< leaf->toString(true);
    return 0;
}