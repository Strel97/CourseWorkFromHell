#include "teamcontroller.h"

TeamController::TeamController()
{
}


Team* TeamController::findByName(string name)
{
	for (int i = 0; i < _teams.size(); i++)
		if (_teams[i].getName() == name)
			return &_teams[i];

	return 0;
}
/*
xml_node* TeamController::serialize(xml_document* doc)
{
    xml_node* teams_node = doc->allocate_node(node_element, "teams");
    teams_node->append_attribute(doc->allocate_attribute("size", itoa( _container.size() )));

    for (vector<team>::iterator iter = _container.begin(); iter != _container.end(); iter++)
    {
        xml_node<>* team_node = doc->allocate_node(node_element, "team");

        team_node->append_attribute(doc->allocate_attribute("name", iter->_name));
        team_node->append_attribute(doc->allocate_attribute("surname", iter->_surname));
        team_node->append_attribute(doc->allocate_attribute("birthday", iter->_birthday));
        team_node->append_attribute(doc->allocate_attribute("status", iter->_status));
        team_node->append_attribute(doc->allocate_attribute("health", iter->_health));
        team_node->append_attribute(doc->allocate_attribute("salary", itoa( iter->_salary )));

        teams_node->append_node(team_node);
    }

    return teams_node;
}

void TeamController::deserialize(xml_node* teams_node)
{
    for (xml_node<>* team_node = teams_node->first_node("team"); team_node; team_node = team_node->next_sibling())
    {
        team team;

        team.setName( team_node->first_attribute("name")->value() );
        team.setSurname( team_node->first_attribute("surname")->value() );
        team.setBirthday( team_node->first_attribute("birthday")->value() );
        team.setStatus( team_node->first_attribute("status")->value() );
        team.sethealth( team_node->first_attribute("health")->value() );
        team.setSalary( atoi(team_node->first_attribute("salary")->value()) );

        _container.push_back(team);
    }
}
*/
