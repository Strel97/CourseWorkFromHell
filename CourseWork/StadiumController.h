#pragma once


#include <vector>

#include "stadium.h"
#include "Controller.h"

using namespace std;

class StadiumController : public Controller<Stadium>
{
public:
	StadiumController(void);
	~StadiumController(void);

	void		edit(int id, string field, string value);

	Stadium*	searchById(int);
	Stadium*	searchByName(string);

    xml_node<>* serialize(xml_document<>* doc);
    void deserialize(xml_node<>*);
};

