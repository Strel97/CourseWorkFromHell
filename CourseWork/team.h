#ifndef TEAM_H
#define TEAM_H


#include <QRegExp>
#include <QString>

#include <iostream>
#include <vector>
#include <string>

#include "player.h"


#define PLAYER_CNT 11;

using namespace std;

/**
 * @brief The Team class    Describes the footbal team
 *
 * It has 11 players and name of team. This class
 * contains functions for player management
 */
class Team
{
public:
    Team();

    /**
     *  Creates empty team with the name, specified
     *  in parameter
     */
    Team(string);

    /**
     * @brief Team  Creates team with the name specified
     * in parameter and with players, specified in parameter
     */
    Team(string, vector<Player>);


    /**
     * @brief getName   Returns the name of team
     * @return          The name of team
     */
    string  getName();


    /**
     * @brief setName   Changes the name of team
     */
    void    setName(string);


    /**
     * @brief addPlayer     Adds player to team
     */
    void addPlayer(Player);

    /**
     * @brief delPlayer     Deletes player from team
     */
    void delPlayer(Player);


    /**
     * @brief isFull    Determines whether the team is full
     * @return          Whether the team is full
     *
     * Team is full, if it has 11 players
     */
    bool isFull();

    /**
     * @brief isEmpty   Determines whether the team is empty
     * @return          Whether the team is empty
     *
     * Team is empty, if it has no players
     */
    bool isEmpty();
	

    /**
     * @brief validateName  Validates name
     * @return              Whether the name meets the following conditions
     *
     * First character of name must be captilized and other must be in lower case.
     * Name must contain only letters.
     */
	static bool validateName(string);


    /**
     * @brief to_console    Outputs the information about team to console
     */
    void to_console();


    /**
     * @brief operator ==       Compares two Team objects
     * @return                  Whether two objects are equal
     *
     * Two Team objects are equal if they have the same
     * name, capacity and pric for one ticket
     */
    friend bool operator== (Team, Team);

    /**
     * @brief operator <<       Outputs the information about object to stream
     * @param os                Output stream
     * @param player            Object for outputting
     * @return                  Output stream
     */
	friend ostream& operator<<(ostream& os, const Team& team);

private:
    /**
     * @brief _name     The name of team
     */
    string _name;

    /**
     * @brief _team     Players list
     */
    vector<Player> _team;
};

#endif // TEAM_H
