#ifndef GAME_H
#define GAME_H

#include <QRegExp>
#include <QString>

#include <string>

#include "team.h"


using namespace std;

/**
 * @brief The GameResults enum      Contains possible variants of game result
 *
 * WIN - First team wins
 * DEFEAT - Opponent team wins
 * DRAW - Nobody wins
 * NOT_PLAYED - The game wasn't played
 */
enum GameResults {WIN, DEFEAT, DRAW, NOT_PLAYED};

/**
 * @brief The Game class    Describes football game
 *
 * This class describes football game. It has the information
 * about teams, date, place of game and amount of viewers.
 * If game was already played, than it also contains the result.
 */
class Game
{
	friend class DateComparer;
	friend class ResultComparer;

public:
    Game();
	Game(string team, string opponent, string date, string place, int viewers);
    Game(Team team, Team opponent, string date, string place, int viewers);

    /**
     * @brief setTeam       Changes the first team in game
     */
	void setTeam(Team);

    /**
     * @brief setOpponent   Changes the opponent team in game
     */
	void setOpponent(Team);

    /**
     * @brief setDate       Changes the date of game
     */
    void setDate(string);

    /**
     * @brief setPlace      Changes the place of game
     */
    void setPlace(string);

    /**
     * @brief setViewers    Changes the number of viewers in game
     */
    void setViewers(int);

    /**
     * @brief setResult     Changes the result of game
     */
    void setResult(int);


    /**
     * @brief getTeam   Returns the first team
     * @return          First team
     */
	Team	getTeam();

    /**
     * @brief getOpponent   Returns the opponent team
     * @return              Opponent team
     */
	Team	getOpponent();

    /**
     * @brief getDate       Returns the date of game
     * @return              Date of game
     */
	string	getDate();

    /**
     * @brief getPlace      Returns the place of game
     * @return              Place of game
     */
	string	getPlace();

    /**
     * @brief getViewers    Returns the number of viewers in game
     * @return              The number of viewers
     */
	int		getViewers();

    /**
     * @brief getResult     Returns the result of game
     * @return              Result of game
     */
    int     getResult();

    /**
     * @brief validateDate      Validates the date of game
     * @return                  Whether the date of game meets the following conditions
     *
     * Date string must satisfy the foolowing mask: XX.XX.XXXX
     * where {day}.{month}.{year}
     * For example: 12.12.1212
     */
	static bool validateDate(string);

    /**
     * @brief validateViewers   Validates the number of viewers in game
     * @return                  Whether the number of viewers meets the following conditions
     *
     * Viewers number must be greater than zero and less than
     * stadium's capacity number
     */
	static bool validateViewers(int);

    /**
     * @brief validateResult    Validates the result of game
     * @return                  Whether the result of game meets the following conditions
     */
	static bool validateResult(int);

    /**
     * @brief validateModification  Validates the field modification parameters
     * @param field                 The name of field
     * @param value                 The new value of field
     * @return                      Whether this modification meets the following conditions
     *
     * Field must be one of the following strings: TEAM, OPPONENT, DATE, VIEWERS, PLACE, VIEWERS or RESULT
     * Value must satisfy the conditions of value of corresponding field.
     */
	static bool validateModification(string field, string value);	

    /**
     * @brief operator ==       Compares two Game objects
     * @return                  Whether two objects are equal
     *
     * Two Game objects are equal if they have the same
     * team, opponent team, date, place, viewers and result
     */
    friend bool operator== (Game, Game);

    /**
     * @brief operator <<       Outputs the information about object to stream
     * @param os                Output stream
     * @param player            Object for outputting
     * @return                  Output stream
     */
	friend ostream& operator<<(ostream& os, const Game& game);

private:	
    /**
     * @brief _team         First team
     */
    Team    _team;

    /**
     * @brief _opponent     Opponent team
     */
    Team    _opponent;

    /**
     * @brief _date         Date of game
     */
    string  _date;

    /**
     * @brief _place        Place of game
     */
    string  _place;

    /**
     * @brief _viewers      The number of viewers
     */
    int     _viewers;

    /**
     * @brief _result       The result of game
     */
    int     _result;
};

/**
 * @brief The DateComparer class    Compares two Game objects on the grounds of their dates
 *
 * Is used in sorting of Game objects by date
 */
class DateComparer
{
public:
	bool operator() (const Game &a, const Game &b)
	{
		string date_a = a._date;
		string date_b = b._date;

		reverse(date_a.begin(), date_a.end());
		reverse(date_b.begin(), date_b.end());

		return date_a < date_b;
	}
};

/**
 * @brief The ResultComparer class  Compares the result of Game objects by their results
 *
 * Is used in sorting of Game objects by result
 */
class ResultComparer
{
public:
	bool operator() (const Game &a, const Game &b)
	{
		return a._result < b._result;
	}
};

#endif // GAME_H
