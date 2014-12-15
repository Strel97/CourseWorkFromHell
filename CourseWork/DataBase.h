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

class DataBase
{
public:
	DataBase(void);
	~DataBase(void);
	
	void			addPlayer(Player);
	void			delPlayer(int id);
	void			editPlayer(int id, string field, string value);
	Player*			getPlayer(int id);
	Player*			getPlayer(string name);
	vector<Player>	getAllPlayers();

	void			addGame(Game);
	void			delGame(int);
	void			editGame(int id, string field, string value);
	Game*			getGame(int id);
	Game*			getGameByDate(string date);
	Game*			getGameByOpponent(string opponent);
	vector<Game>	getAllGames();
	void			sortGamesByDate();
	void			sortGamesByResult();

	void			addStadium(Stadium);
	void			delStadium(int id);
	void			editStadium(int id, string field, string value);
	Stadium*		getStadium(int id);
	Stadium*		getStadium(string name);
	vector<Stadium>	getAllStadiums();

    void            saveToFile();
    void            loadFromFile();
    string          getDBFileName();

private:
	PlayerController _player_controll;
	GameController	 _game_controll;
	StadiumController _stadium_controll;
	TeamController	 _team_controll;
};

