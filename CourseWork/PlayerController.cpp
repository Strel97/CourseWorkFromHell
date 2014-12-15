#include "PlayerController.h"


void PlayerController::edit(int id, string field, string value)
{
    if (validateID(id))
	{
		Player player = _container[id];
		
		if (field == "NAME")
			player.setName(value);
		else if (field == "SURNAME")
			player.setSurname(value);
		else if (field == "BIRTHDAY")
			player.setBirthday(value);
		else if (field == "STATUS")
			player.setStatus(value);
		else if (field == "HEALTH")
			player.setHealth(value);
		else if (field == "SALARY")
			player.setSalary(stoi(value));

		_container[id] = player;
	}
}

Player* PlayerController::searchById(int id)
{
    if (validateID(id))
		return &_container[id];

	return 0;
}

Player* PlayerController::searchByName(string name)
{
	for (int i = 0; i < _container.size(); i++)
		if (_container[i].getName() == name)
			return &_container[i];

	return 0;
}

xml_node<>* PlayerController::serialize(xml_document<>* doc)
{
    xml_node<>* players_node = doc->allocate_node(node_element, "players");
    players_node->append_attribute(doc->allocate_attribute("size", Functions::itoa( _container.size() )));

    for (vector<Player>::iterator iter = _container.begin(); iter != _container.end(); iter++)
    {
        xml_node<>* player_node = doc->allocate_node(node_element, "player");

        player_node->append_attribute(doc->allocate_attribute("name", iter->getName().c_str() ));
        player_node->append_attribute(doc->allocate_attribute("surname", iter->getSurname().c_str() ));
        player_node->append_attribute(doc->allocate_attribute("birthday", iter->getBirthday().c_str() ));
        player_node->append_attribute(doc->allocate_attribute("status", iter->getStatus().c_str() ));
        player_node->append_attribute(doc->allocate_attribute("health", iter->getHealth().c_str() ));
        player_node->append_attribute(doc->allocate_attribute("salary", Functions::itoa( iter->getSalary() )));

        players_node->append_node(player_node);
    }

    return players_node;
}

void PlayerController::deserialize(xml_node<>* players_node)
{
    _container.clear();

    for (xml_node<>* player_node = players_node->first_node("player"); player_node; player_node = player_node->next_sibling())
    {
        Player player;

        player.setName( player_node->first_attribute("name")->value() );
        player.setSurname( player_node->first_attribute("surname")->value() );
        player.setBirthday( player_node->first_attribute("birthday")->value() );
        player.setStatus( player_node->first_attribute("status")->value() );
        player.setHealth( player_node->first_attribute("health")->value() );
        player.setSalary( atoi(player_node->first_attribute("salary")->value()) );

        _container.push_back(player);
    }
}
