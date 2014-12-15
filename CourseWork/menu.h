#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "DataBase.h"
#include "functions.h"
#include "player.h"
#include "game.h"
#include "stadium.h"


#define ERR_INVALID_CMD 0

using namespace std;

class Menu
{
public:
    Menu();

    void start();
    string getCommand();
    void parseCommand(string cmd);
    void showHelp();

    void addPlayer();
    void delPlayer();
    void modifyPlayer();
    void showPlayer();
    void showAllPlayers();
	void searchPlayer();

    void addGame();
    void delGame();
    void modifyGame();
	void setGameResult();
    void showGame();
    void showAllGames();
	void sortGamesByDate();
	void sortGamesByResult();
	void searchGameByDate();
	void searchGameByOpponent();

	void addStadium();
    void delStadium();
    void modifyStadium();
    void showStadium();
    void showAllStadiums();
	void searchStadium();

    void saveDbToFile();
    void loadDbFromFile();

    void error(int code);

private:    
    vector<string> ErrDescription;
	DataBase database;
};

#endif // MENU_H
