#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <QRegExp>
#include <QString>
#include "functions.h"


using namespace std;

/**
 * @brief The Player class  Describes the player
 *
 * It contains information about player as a person(name, surname, birthday)
 * and his characteristics as a football player(status, health, salary)
 */
class Player
{
public:
    Player();

    /**
     * @brief Player        Creates new instance of Player object
     * @param name          Player's name
     * @param surname       Player's surname
     * @param birthday      Player's birthday
     * @param status        Player's status
     * @param health        Player's health
     * @param salary        Player's salary
     */
	Player(string name, string surname, string birthday, string status, string health, int salary);

    // Getters
    /**
     * @brief getName   Returns the name of player
     * @return          Name of Player
     */
    string  getName();

    /**
     * @brief getSurname    Returns the surname of Player
     * @return              The surname of Player
     */
    string  getSurname();

    /**
     * @brief getBirthday   Returns the birthday of Player
     * @return              The birthday of Player
     */
    string  getBirthday();

    /**
     * @brief getStatus     Returns the status of Player in team (ATTACK, DEFENCE, GOALKEEPER)
     * @return              The status of Player in team
     */
    string  getStatus();

    /**
     * @brief getHealth     Returns the status of health of Player (SICK, HEALTHY)
     * @return              The status of health of Player
     */
    string  getHealth();

    /**
     * @brief getSalary     Returns the salary of Player
     * @return              The salary of Player
     */
    int     getSalary();

    // Setters	
    /**
     * @brief setName       Changes the player's name
     */
    void setName(string);

    /**
     * @brief setSurname    Changes the player's surname
     */
    void setSurname(string);

    /**
     * @brief setBirthday   Changes the player's birthday
     */
	void setBirthday(string);

    /**
     * @brief setStatus     Changes the player's status in team
     */
    void setStatus(string);

    /**
     * @brief setHealth     Changes the player's status of health
     */
    void setHealth(string);

    /**
     * @brief setSalary     Changes the player's salary
     */
    void setSalary(int);

    // Methods validators
    /**
     * @brief validateName  Validates name
     * @return              Whether the name meets the following conditions
     *
     * First character of name must be captilized and other must be in lower case.
     * Name must contain only letters.
     */
    static bool validateName(string);

    /**
     * @brief validateSurname   Validates surname
     * @return                  Whether the surname meets the following conditions
     *
     * First character of surname must be captilized and other must be in lower case.
     * Surname must contain only letters
     */
    static bool validateSurname(string);

    /**
     * @brief validateBirthday  Validates birthday
     * @return                  Whether the birthday meets the following conditions
     *
     * Birthday string must satisfy the foolowing mask: XX.XX.XXXX
     * where {day}.{month}.{year}
     * For example: 12.12.1212
     */
    static bool validateBirthday(string);

    /**
     * @brief validateStatus    Validates status of player
     * @return                  Whether the status meets the following conditions
     *
     * Status must be one of the following strings: ATTACK, DEFENCE or GOALKEEPER
     */
    static bool validateStatus(string);

    /**
     * @brief validateHealth    Validates status of health of player
     * @return                  Whether the status of health meets the following conditions
     *
     * Health must be one of the following strings: SICK or HEALTHY
     */
    static bool validateHealth(string);

    /**
     * @brief validateSalary    Validates salary value of player
     * @return                  Whether the salary meets the following conditions
     *
     * Salary value must be greater than zero and less than 10000
     */
    static bool validateSalary(int);

    /**
     * @brief validateModification  Validates the field modification parameters
     * @param field                 The name of field
     * @param value                 The new value of field
     * @return                      Whether this modification meets the following conditions
     *
     * Field must be one of the following strings: NAME, SURNAME, BIRTHDAY, STATUS, HEALTH, SALARY
     * Value must satisfy the conditions of value of corresponding field.
     */
	static bool validateModification(string field, string value);

    // Operators
    /**
     * @brief operator ==       Compares two Player objects
     * @return                  Whether two objects are equal
     *
     * Two Player objects are equal if they have the same
     * name, surname, birthday, status, health and salary
     */
    friend bool     operator== (Player, Player);

    /**
     * @brief operator <<       Outputs the information about object to stream
     * @param os                Output stream
     * @param player            Object for outputting
     * @return                  Output stream
     */
    friend ostream& operator<<(ostream& os, const Player& player);

private:	
    /**
     * @brief _name     The name of Player
     */
    string  _name;

    /**
     * @brief _surname  The surname of Player
     */
    string  _surname;

    /**
     * @brief _birthday The birthday of Player
     */
    string  _birthday;

    /**
     * @brief _status   The status of Player in team
     */
    string  _status;

    /**
     * @brief _health   The status of health of Player
     */
    string  _health;

    /**
     * @brief _salary   The salary of Player
     */
    int     _salary;
};

#endif // PLAYER_H
