#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>


using namespace std;

class Functions
{
public:
    static vector<string> split(string str, char delim);
    static const char* itoa(int value);
};

#endif // FUNCTIONS_H
