#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>


using namespace std;

/**
 * @brief The Functions class   Contains some help functions
 *
 * This class is utilite for other classes
 */
class Functions
{
public:
    /**
     * @brief itoa      Converts integer value to string
     * @param value     Integer value
     * @return          C String
     */
    static const char* itoa(int value);
};

#endif // FUNCTIONS_H
