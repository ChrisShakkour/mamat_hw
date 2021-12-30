#ifndef IP_H
#define IP_H

#include <iostream>
#include <cstring>
#include "field.h"
#include "string.h"

class Ip : public Field {
private:
    unsigned int rule;
    int rule_len;
    
    /**
     * @brief Converting the ip to unsigned int
     * @param ip_adress An IP address
     * @return the integer that is represented by the IP in the parameter
     */
    unsigned int ip_to_int(String ip_address) const;
    
    /**
     * @brief Keeping only the requested MSBs of the IP
     * @param num A converted int from IP address
     * @param rule_len determines the number of MSBs that should
     * @return Representation of the rule by unsigned int
     */
    unsigned int calculate_msbits(unsigned int num, int rule_len) const;
public:

    /**
     * @brief Constructor
     * @param pattern: The type of field of the rule 
     * @return the constructed "Ip" object
     */
    Ip(String pattern);
    
    /**
     * @brief Destructor
     */
    ~Ip();
    
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