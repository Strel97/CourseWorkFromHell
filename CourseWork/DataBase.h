#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include "player.h"
#include "game.h"
#include "stadium.h"
#include "PlayerController.h"
#include "GameController.h"
#include "StadiumController.h"
#include "Controller.h"

#include <RapidXml/rapidxml.hpp>
#include <RapidXml/rapidxml_utils.hpp>
#include <RapidXml/rapidxml_print.hpp>

using namespace std;
using namespace rapidxml;

/**
 * @brief The DataBase class    Imitates the work of DataBase
 *
 * This class contains methods for players, teams, stadiums and games
 * managing
 */
class DataBase
{
public:
	DataBase(void);
	~DataBase(void);
	

    /**
     * @brief addPlayer     Adds new Player to database
     */
	void			addPlayer(Player);

    /**
     * @brief delPlayer     Deletes existing Player from database
     * @param id            ID of player in DB
     */
	void			delPlayer(int id);

    /**
     * @brief editPlayer    Changes information about Player in DB
     * @param id            ID of player in DB
     * @param field         Field to change
     * @param value         New value of field
     */
	void			editPlayer(int id, string field, string value);

    /**
     * @brief getPlayer     Searches and returns player from DB
     * @param id            ID of player in DB
     * @return              Pointer to Player object
     *
     * It searches player by specified id in DB
     */
	Player*			getPlayer(int id);

    /**
     * @brief getPlayer     Searches and returns player from DB
     * @param id            ID of player in DB
     * @return              Pointer to Player object
     *
     * It searches player by specified name in DB
     */
	Player*			getPlayer(string name);

    /**
     * @brief getAllPlayers     Returns all players from DB
     * @return                  Players list
     */
	vector<Player>	getAllPlayers();


    /**
     * @brief addGame     Adds new Game to database
     */
	void			addGame(Game);

    /**
     * @brief delGame   Deletes existing Game from database by
     * specified id
     */
	void			delGame(int);

    /**
     * @brief editGame      Changes information about Game in DB
     * @param id            ID of game in DB
     * @param field         Field to change
     * @param value         New value of field
     */
	void			editGame(int id, string field, string value);

    /**
     * @brief getGame       Searches and returns game from DB
     * @param id            ID of game in DB
     * @return              Pointer to Game object
     *
     * It searches game by specified id in DB
     */
	Game*			getGame(int id);

    /**
     * @brief getGameByDate     Searches and returns game from DB
     * @param date              Date of game
     * @return                  Pointer to Game object
     *
     * It searches game by specified date in DB
     */
	Game*			getGameByDate(string date);

    /**
     * @brief getGameByOpponent     Searches and returns game from DB
     * @param opponent              Opponent team name
     * @return                      Pointer to Game object
     *
     * It searches game by specified opponent teamname in DB
     */
	Game*			getGameByOpponent(string opponent);

    /**
     * @brief getAllGames   Returns the list of all games from db
     * @return              List of all games
     */
	vector<Game>	getAllGames();

    /**
     * @brief sortGamesByDate       Sortes games by date in db
     */
	void			sortGamesByDate();

    /**
     * @brief sortGamesByResult     Sortes game by result in db
     */
	void			sortGamesByResult();


    /**
     * @brief addStadium    Adds new Stadium to database
     */
	void			addStadium(Stadium);

    /**
     * @brief delStadium    Deletes existing Stadium from database
     * @param id            ID of stadium to delete
     */
	void			delStadium(int id);

    /**
     * @brief editStadium   Changes information about Stadium in DB
     * @param id            ID of stadium in DB
     * @param field         Field to change
     * @param value         New value of field
     */
	void			editStadium(int id, string field, string value);

    /**
     * @brief getStadium    Searches and returns stadium from DB
     * @param id            ID of stadium in DB
     * @return              Pointer to Stadium object
     *
     * It searches stadium by specified id in DB
     */
	Stadium*		getStadium(int id);

    /**
     * @brief getStadium    Searches and returns stadium from DB
     * @param name          The name of stadium
     * @return              Pointer to Stadium object
     *
     * It searches stadium by specified name in DB
     */
	Stadium*		getStadium(string name);

    /**
     * @brief getAllStadiums    Returns the list of all stadiums from db
     * @return                  List of all stadiums
     */
	vector<Stadium>	getAllStadiums();


    /**
     * @brief saveToFile    Serializes the whole database
     */
    void            saveToFile();

    /**
     * @brief loadFromFile  Deserializes database
     */
    void            loadFromFile();

    /**
     * @brief getDBFileName     Returns database name
     * @return                  DB name
     */
    string          getDBFileName();

private:
    /**
     * @brief _player_controll      Controller class for players manipulations
     */
	PlayerController _player_controll;

    /**
     * @brief _game_controll        Controller class for games manipulations
     */
	GameController	 _game_controll;

    /**
     * @brief _stadium_controll     Controller class for stadiums manipulations
     */
	StadiumController _stadium_controll;

    /**
     * @brief _team_controll        Controller class for teams manipulations
     */
	TeamController	 _team_controll;
};

