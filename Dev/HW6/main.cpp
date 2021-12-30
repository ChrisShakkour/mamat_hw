#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "string.h"
#include "input.h"

#define ERROR -1
#define DOUBLE 2

using namespace std;

/**
 * @brief This line briefly describes the method operation.
 * @param argc The number of arguments 
 * @param argv The array of the arguments - argv[1] should be the rule
 * @return 0 on success and -1 otherwise
 */
int main(int argc, char **argv) {
    if (check_args(argc, argv)) {
        return ERROR;
    }
    int input_len = (strlen(argv[1]) + 1);
    char *temp = new char[input_len];
    strcpy(temp,argv[1]);
    for (int i = 0; i < input_len; i++) {
        if (temp[i] == ',' || temp[i] == '\t') {
            temp[i] = ' ';
        }
    }
    String rule(temp);
    delete[] temp;
    String *subs;
    size_t num_of_subs = 0;
    rule.trim().split("=", &subs, &num_of_subs);

    if ((int)num_of_subs != DOUBLE) {
        delete[] subs;
        return ERROR;
    }

    String field_type = subs[0].trim();
    String rule_val = subs[1].trim();

    if (field_type.equals("src-ip")) {
        Ip src_ip(field_type);
        src_ip.set_value(rule_val);
        parse_input(src_ip);
    }

    else if (field_type.equals("src-port")) {
        Port src_port(field_type);
        src_port.set_value(rule_val);
        parse_input(src_port);
    }
            
    else if (field_type.equals("dst-ip")) {
        Ip dst_ip(field_type);
        dst_ip.set_value(rule_val);
        parse_input(dst_ip);
    }
        
    else {
        Port dst_port(field_type);
        dst_port.set_value(rule_val);
        parse_input(dst_port);
    }

    delete[] subs;
    return 0;
}