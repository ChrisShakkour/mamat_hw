#include <iostream>
#include <cstring>
#include "field.h"

#define DOUBLE 2
#define FIELDS 4


Field::Field(String pattern) :
      pattern(pattern) {

}


Field::~Field() {
    
}


bool Field::match(String packet){
    String *subs;
    size_t size = 0;
    packet.split(",=", &subs, &size);
    if(!size){
        delete[] subs;
        return false;
    }
    bool is_match = false;
    String temp;
    for(int i = 0; i<(int)size; i+=DOUBLE){
        temp = subs[i].trim();
        if(pattern.equals(temp)) {
            is_match = match_value(subs[i + 1].trim());
            delete[] subs;
            return is_match;
        }
    }
    delete[] subs;
    return is_match;    
}