#include "ip.h"

#define CONVERTING_FAILED -1
#define INIT 1
#define DOUBLE 2
#define SUBS 2
#define IP_ELEMENTS 4
#define BYTE 8
#define BITS 32
#define HALF_LAR 2147483648

#define FIRST  0
#define SECOND 1
#define THIRD  2
#define FOURTH 3
#define MAX_VALUE_IP 255


Ip::Ip(String pattern)
    : Field(pattern) {
    
}

Ip::~Ip() {

}


unsigned int Ip::ip_to_int(String ip_address) const { 
     unsigned int integer_string = 0;
    String *ptr_string;
    size_t string_size = 0;
    ip_address.split(".", &ptr_string, &string_size);  
    int first_ip = ptr_string[FIRST].trim().to_integer();
    int second_ip = ptr_string[SECOND].trim().to_integer();
    int third_ip = ptr_string[THIRD].trim().to_integer();
    int fourth_ip = ptr_string[FOURTH].trim().to_integer();       
    integer_string = (first_ip << FOURTH*BYTE) | (second_ip << THIRD*BYTE) 
    | (third_ip << SECOND*BYTE) | (fourth_ip);
    delete[] ptr_string;
    return integer_string;
}


unsigned int Ip::calculate_msbits(unsigned int num, int rule_len) const {
    
    unsigned int res = (num < HALF_LAR) ? (HALF_LAR | num) : num;
    res = res >> (BITS - rule_len);
    return (num < HALF_LAR) ? (res - (HALF_LAR >> (BITS - rule_len))) : res;

}


bool Ip::set_value(String val) {
    
    String *subs;
    size_t num_of_subs = 0;
    val.split("/", &subs, &num_of_subs);
    
    if (num_of_subs != SUBS) {
        delete[] subs;
        return false;
    }
    
    unsigned int x = ip_to_int(subs[0].trim());
    rule_len = subs[1].trim().to_integer();
    delete[] subs;
    rule = calculate_msbits(x, rule_len);
    return true;

}


bool Ip::match_value(String packet) const {

    unsigned int x = ip_to_int(packet.trim());
    unsigned int to_compare = calculate_msbits(x, rule_len);
    return (bool)(to_compare == rule);

}