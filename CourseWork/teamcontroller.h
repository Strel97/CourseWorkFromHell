#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H


#include <vector>

#include "team.h"
#include "player.h"

#include <RapidXml/rapidxml.hpp>


using namespace std;
using namespace rapidxml;

class TeamController
{
public:
    TeamController();

    Team* findByName(string);

    xml_node<>* serialize(xml_document<>* doc);
    void deserialize(xml_node<>*);

private:
    vector<Team> _teams;
};

#endif // TEAMCONTROLLER_H
