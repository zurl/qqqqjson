#include "json.h"


//extern int testJSONParser();




int main(){
    JSON * json = JSON::fromFile("input.json");
    if( json != nullptr)std::cout<< json->toString(true);
    //JSON * leaf = json->path(".mysql.admin.group[0].username");
    //if(leaf != nullptr) std::cout<< leaf->toString(true);
    // JSONArray * json = new JSONArray();
    // for(int i =1;i<=1000000;i++){
    //     std::ostringstream os;
    //     os<<i;
    //     json->elements.emplace_back(new JSONString(os.str()));
    // }
    // std::cout<<json->toString();
    // return 0;
}