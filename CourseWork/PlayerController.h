#pragma once


#include <vector>

#include "player.h"
#include "Controller.h"


using namespace std;

class PlayerController : public Controller<Player>
{
public:

    void		edit(int id, string field, string value);

	Player*		searchById(int);
	Player*		searchByName(string);

    xml_node<>* serialize(xml_document<>* doc);
    void deserialize(xml_node<>*);
};

