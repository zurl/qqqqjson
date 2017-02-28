#include "json.h"

std::string getIndent(size_t indent){
    std::string result = "";
    for(size_t i = 0; i < indent; i ++ )
        result += "  ";
    return result;
}

JSONString::JSONString( const char * str , size_t n ): str(str, n){}
std::string JSONString::toString(bool format, size_t indent)  {
    return "\"" + str + "\"";
}
JSON::Type JSONString::type() { return JSON::Type::String; }

JSONInteger::JSONInteger( long long value ): value(value){}
std::string JSONInteger::toString(bool format, size_t indent) {
    std::ostringstream os;
    os << value;
    return os.str();
}
JSON::Type JSONInteger::type() { return JSON::Type::Integer; }

JSONDouble::JSONDouble( double value) : value( value ){}
std::string JSONDouble::toString(bool format, size_t indent) {
    std::ostringstream os;
    os << value;
    return os.str();
}
JSON::Type JSONDouble::type() { return JSON::Type::Double; }

JSONObject::JSONObject(){}
JSONObject::~JSONObject(){
    for( auto & pair : hashMap ){
        delete pair.second;
    }
}
std::string JSONObject::toString(bool format, size_t indent) {
    std::ostringstream os;
    os << "{"; 
    if( format && hashMap.size() != 0) os << std::endl;
    size_t index = hashMap.size();
    for( auto & pair : hashMap){
        index --;
        if( format ) os << getIndent(indent + 1);
        os << "\"" << pair.first << "\"" << ":";
        if( format ) os << " ";
        os << pair.second->toString(format, indent + 1);
        if(index) os << ",";
        if( format ) os << std::endl;
    }
    if( format ) os << getIndent(indent);
    os << "}";
    return os.str();
}

JSON::Type JSONObject::type() { return JSON::Type::Object; }

JSONBoolean::JSONBoolean(bool value) : value( value ){}
std::string JSONBoolean::toString(bool format, size_t indent) {
    if( value ) return "true";
    else return "false";
}
JSON::Type JSONBoolean::type() { return JSON::Type::Boolean; }

JSONArray::~JSONArray(){
    for( auto & item : elements ){
        delete item;
    }
}
std::string JSONArray::toString(bool format, size_t indent) {
    std::ostringstream os;
    os << "["; 
    if( format && elements.size() != 0) os << std::endl;
    size_t index = elements.size();
    for( auto & item : elements){
        index --;
        if( format ) os << getIndent(indent + 1);
        os << item->toString(format, indent + 1);
        if(index)os << ",";
        if( format ) os << std::endl;
    }
    if( format ) os << getIndent(indent);
    os << "]";
    return os.str();
}
JSON::Type JSONArray::type() { return JSON::Type::Array; }

std::string JSONNull::toString(bool format, size_t indent) {
    return "null";
}
JSON::Type JSONNull::type() { return JSON::Type::Null; }

JSON * JSON::get(size_t index){
    if( this->type() != JSON::Type::Array) return nullptr;
    JSONArray * jsonArray = (JSONArray *)this;
    if(index >= jsonArray->elements.size()) return nullptr;
    return jsonArray->elements[index];
}

JSON * JSON::get(const std::string & index){
    if( this->type() != JSON::Type::Object) return nullptr;
    JSONObject * jsonObject = (JSONObject *)this;
    auto iter = jsonObject->hashMap.find(index);
    if( iter == jsonObject->hashMap.end()) return nullptr;
    else return iter->second;
}

JSON * JSON::get(const char * index){
    return this->get(std::string(index));
}

JSONInteger * JSON::toInteger(){
    if( this->type() != JSON::Type::Integer) return nullptr;
    JSONInteger * jsonInteger = (JSONInteger *)this;
    return jsonInteger;
}

JSONDouble * JSON::toDouble(){
    if( this->type() != JSON::Type::Double) return nullptr;
    JSONDouble * jsonDouble = (JSONDouble *)this;
    return jsonDouble;
}

char jsonBuffer [ 65536 * 64 ];
JSON * JSON::fromFile(const char * fileName){
    FILE * file = fopen(fileName, "r");
    if( !file )return nullptr;
    size_t now = 0;
    jsonBuffer[0] = fgetc(file);
    while(jsonBuffer[now] != EOF)jsonBuffer[++now] = fgetc(file);
    JSON * json = JSON::parse(jsonBuffer);
    fclose(file);
    return json;
}

void JSON::saveIntoFile(const char * fileName, bool format = true){
    FILE * file = fopen(fileName, "w");
    if( !file )return nullptr;
    fputs(file, this->toString(format));
    close(file);
}