#include "functions.h"

vector<string> Functions::split(string str, char delim)
{
    vector<string> tokens;
    int word_end_pos = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == delim)
        {
            tokens.push_back( str.substr(word_end_pos, i) );
            word_end_pos = i;
        }
    }

    return tokens;
}

const char* Functions::itoa(int value)
{    
    return to_string(value).c_str();
}
