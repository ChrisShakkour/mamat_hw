#include "port.h"

#define SUBS 2
#define MAX_VAL_PORT 65535
//-----------------------------------------------------------------------------

//constructor
Port::Port(String pattern) : Field(pattern) {

}

//-----------------------------------------------------------------------------

//destructor
Port::~Port() {

}

//-----------------------------------------------------------------------------

//define a set of valid values to the port
bool Port::set_value(String val) {
    size_t num_of_sub_string = 0;
    String *subs;
    val.split("-", &subs, &num_of_sub_string);
    if (num_of_sub_string == SUBS) {
        down_value = subs[0].trim().to_integer();
        up_value = subs[1].trim().to_integer();
        delete[] subs;
        if (down_value <= up_value) {
            if ((down_value <= MAX_VAL_PORT) && (0 <= down_value) &&
                (up_value <= MAX_VAL_PORT) && (0 <= down_value)) {
                return true;
            }

        }
    }
    return false;
}

//-----------------------------------------------------------------------------

//check if the variable matches the set of value
bool Port::match_value(String packet) const {
    int v_port=packet.trim().to_integer();
    if ((v_port <= up_value) && (v_port >= down_value)) {
        return true;
    }
    else {
        return false;
    }
}

//-----------------------------------------------------------------------------