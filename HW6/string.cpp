#include "string.h"
#include <iostream>
#include <cstring>

//-----------------------------------------------------------------------------
// default constructor
String::String() {

    length = 0;
    data = new char[1];
    data[0] = '\0';
    
}

//-----------------------------------------------------------------------------

// copy constructor
String::String(const String &str){

    if (!str.data) {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }

    else {
        length = str.length;
        data = new char[length + 1];
        strcpy(data, str.data);
    }
    
}

//-----------------------------------------------------------------------------

//constructor

String::String(const char *str) {

    if (!str) {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }

    else {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
}

//-----------------------------------------------------------------------------
//destructor
String::~String() {

    delete[] data;
    
}

//-----------------------------------------------------------------------------
//changes this from string
String& String::operator=(const String &rhs) {

    if (!rhs.data) {
        delete[] data;
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return *this;
    }
    
    else if (this == &rhs ) {
        return *this;
    }
        
    else  {
        delete[] data;
        length = rhs.length;
        data = new char[length + 1];
        strcpy(data, rhs.data);
        return *this;
    }

}

//-----------------------------------------------------------------------------
//changes this from char array

String& String::operator=(const char *str) {
    
    if (!str) {
        delete[] data;
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return *this;
    }
    
    else if (length == strlen(str) && !strcmp(data, str)) {
        return *this;
    }

    else {
        delete[] data;
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        return *this;
    }

}
//-----------------------------------------------------------------------------
//ruturn true iff the contents of this equals to the contents of rhs
bool String::equals(const String &rhs) const {

    if (!rhs.data) {
        return (bool)!length;
    }
    
    if ((length == rhs.length) && !strcmp(data, rhs.data)) {
        return true;
    }

    return false;
}
//-----------------------------------------------------------------------------
//returns true iff the contents of this equals to rhs
bool String::equals(const char *rhs) const {

    if (!rhs) {
        return (bool)!length;
    }
    
    if ((length == strlen(rhs)) && !strcmp(data,rhs)) {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
//splits this to several sub_strings according to delimiters
void String::split(const char *delimiters, String **output, size_t *size) const{
    int sub_string = 0 , ind_copy = 0, k = 0, ind_string = 0;
    int length_of_delimiters = strlen(delimiters);
    char copy_str[length + 1];

    if( (!delimiters) || !data || !size) {
           return;
    }

    strcpy(copy_str, data);
    copy_str[length] = '\0';

    while ( k++ < (int) length ) {
    int l = 0;
        while( l < length_of_delimiters ) {

            if (data[k] == delimiters[l]) {
         copy_str[k] = '\0';
         ind_copy = 0 ;
             sub_string++;
            }
     l++;
         }
   }
    
   *size = sub_string +  1;

    if (!output){
        return;
    }
    
    else{

    *output = new String[*size];
   
    for( k = 0; k < (int) length; k++) {
       for (int  l = 0 ; l < length_of_delimiters ; l++) {
           if (data[k] == delimiters[l]) {
                (*output)[ind_string++] = String(&copy_str[ind_copy]);
                ind_copy = k + 1;
            }
        }
    }

    (*output)[ind_string] = String(&copy_str[ind_copy]);

    return;
    }
}

//--------------------------------------------------------------------------

//create integer from string. return 0 in case of error
int String::to_integer() const {
    
    return atoi(data);

}

//-----------------------------------------------------------------------------
//remove any leading or trailing white-spaces
String String::trim() const { 
    
    int i = 0, spaces_begin = 0, spaces_end = 0;
    while (data[i] == ' ') {
        spaces_begin++;
        i++;
    }
    
    if (data[i] == '\0') {
        return String();
    }
    
    i = strlen(data) - 1;
    while (data[i] == ' ') {
        spaces_end++;
        i--;
    }
    
    char copy_str[strlen(data) + 1 - spaces_begin - spaces_end];
    copy_str[strlen(data) - spaces_begin - spaces_end] = '\0';
    
    i = 0;
    for (int j = spaces_begin; j < (int)strlen(data) - spaces_end; j++) {
        
        copy_str[i++] = data[j];
    }
    
    return String(copy_str);
}
