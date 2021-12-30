#ifndef PORT_H
#define PORT_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "field.h"
#include "string.h"

//-----------------------------------------------------------------------------


class Port : public Field {
    private:
        int down_value;
        int up_value;
    public:
        /**
         * @brief Constructor
         * @param patte: The type of field of the rule
         * @return the constructed "Port" object
         */ 
        Port(String pattern);
        /**
         * @brief Destructor
         */
        ~Port();
        /**
         * brief Defining the valid values of the field
         * @param val A string of the valid values of the fields
         * @return true if succeeded parsing the input and false otherwise
         */
        bool set_value(String val);
        /**
         * brief Comparing between a packet and the rule
         * @param packet A string of a packet that should be compared
         * @return return true if the packet matches the rule.
         *         otherwise it returns false
         */
        bool match_value(String packet) const;

};

#endif