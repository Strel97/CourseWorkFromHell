#pragma once


#include <vector>

#include "game.h"
#include "teamcontroller.h"
#include "Controller.h"

using namespace std;

class GameController : public Controller<Game>
{
public:
	GameController();
	
	void		edit(int id, string field, string value);
	
	void		sortByDate();
	void		sortByResult();
	
	Game*			searchById(int);	
	Game*			searchByDate(string);	
	Game*			searchByOpponent(string);	
	Game			getGameById(int id);

    xml_node<>* serialize(xml_document<>* doc);
    void deserialize(xml_node<>*);
};

