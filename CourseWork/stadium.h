#ifndef STADIUM_H
#define STADIUM_H


#include <QRegExp>
#include <QString>

#include <string>
#include <vector>

#include "game.h"


using namespace std;

/**
 * @brief The Stadium class     Describes the stadium
 *
 * It contains information about capacity of stadium,
 * price for one ticket and the list of games to be played here
 */
class Stadium
{
public:
    Stadium();
    Stadium(string name, int places, int ticket_price);

    /**
     * @brief setName       Changes the stadium's name
     */
	void setName(string);

    /**
     * @brief setPlaces     Changes the capacity of stadium
     */
    void setPlaces(int);

    /**
     * @brief setTicketPrice    Changes the price for one ticket
     */
    void setTicketPrice(int);


    /**
     * @brief getName       Returns the name of stadium
     * @return              The name of stadium
     */
    string  getName();

    /**
     * @brief getPlaces     Returns the capacity of stadium
     * @return              The capacity of stadium
     */
    int     getPlaces();

    /**
     * @brief getTicketPrice    Returns the price for one ticket
     * @return                  The price for one ticket
     */
    int     getTicketPrice();


    /**
     * @brief addGame       Adds game to the list of games
     */
    void addGame(Game);

    /**
     * @brief delGame       Deletes game from the list of games
     */
    void delGame(Game);


    /**
     * @brief validateName  Validates name
     * @return              Whether the name meets the following conditions
     *
     * First character of name must be captilized and other must be in lower case.
     * Name must contain only letters.
     */
	static bool validateName(string);

    /**
     * @brief validatePlaces    Validates capacity of stadium
     * @return                  Whether the capacity meets the following conditions
     *
     * Capacity must be greater than zero
     */
	static bool validatePlaces(int);

    /**
     * @brief validateTicketPrice   Validates ticket price
     * @return                      Whether the ticket price meets the following conditions
     *
     * Ticket price must be greater than zero
     */
	static bool validateTicketPrice(int);

    /**
     * @brief validateModification  Validates the field modification parameters
     * @param field                 The name of field
     * @param value                 The new value of field
     * @return                      Whether this modification meets the following conditions
     *
     * Field must be one of the following strings: NAME, PLACES, TICKET_PRICE
     * Value must satisfy the conditions of value of corresponding field.
     */
	static bool validateModification(string field, string value);	

    /**
     * @brief operator ==       Compares two Stadium objects
     * @return                  Whether two objects are equal
     *
     * Two Stadium objects are equal if they have the same
     * name, capacity and pric for one ticket
     */
	friend bool     operator== (Stadium, Stadium);

    /**
     * @brief operator <<       Outputs the information about object to stream
     * @param os                Output stream
     * @param player            Object for outputting
     * @return                  Output stream
     */
    friend ostream& operator<<(ostream& os, const Stadium& stadium);

private:
    /**
     * @brief _name     The name of stadium
     */
    string _name;

    /**
     * @brief _places   The capacity of stadium
     */
    int _places;

    /**
     * @brief _ticket_price     The price for one ticket
     */
    int _ticket_price;

    /**
     * @brief _games    The list of games to be played on this stadium
     */
    vector<Game>  _games;
};

#endif // STADIUM_H
