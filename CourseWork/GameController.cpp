#include "GameController.h"


GameController::GameController()
{
	// Just for test!!!
	_container.push_back( Game("Terra", "Incognita", "12.12.1212", "Place", 12) );
	_container.push_back( Game("Terra", "Gut", "12.12.1222", "Place", 12) );
	_container.push_back( Game("Terra", "Buddy", "12.12.3212", "Gewq", 12) );
	_container.push_back( Game("Buddy", "Incognita", "12.12.3222", "Place", 12) );
	_container.push_back( Game("Gut", "Incognita", "12.12.0212", "Gqwe", 12) );
}

void GameController::edit(int id, string field, string value)
{
	if (validateID(id))
	{
		Game game = _container[id];
		
		if (field == "TEAM")
			game.getTeam().setName(value);
		else if (field == "OPPONENT")
			game.getOpponent().setName(value);
		else if (field == "DATE")
			game.setDate(value);
		else if (field == "PLACE")
			game.setPlace(value);
		else if (field == "VIEWERS")
			game.setViewers(stoi(value));
		else if (field == "RESULT")
			game.setResult(stoi(value));

		_container[id] = game;
	}
}

void GameController::sortByDate()
{
	sort(_container.begin(), _container.end(), DateComparer());
}

void GameController::sortByResult()
{
	sort(_container.begin(), _container.end(), ResultComparer());
}

Game* GameController::searchById(int id)
{
	if (validateID(id))
		return &_container[id];

	return 0;
}

Game* GameController::searchByDate(string date)
{
	for (int i = 0; i < _container.size(); i++)
		if (_container[i].getDate() == date)
			return &_container[i];

	return 0;
}

Game* GameController::searchByOpponent(string opponent)
{
	for (int i = 0; i < _container.size(); i++)
		if (_container[i].getOpponent().getName() == opponent)
			return &_container[i];

	return 0;
}

Game GameController::getGameById(int id)
{
	if (validateID(id))
		return _container[id];

	return Game();
}

xml_node<>* GameController::serialize(xml_document<>* doc)
{
    xml_node<>* games_node = doc->allocate_node(node_element, "games");
    games_node->append_attribute(doc->allocate_attribute("size", Functions::itoa(_container.size()) ));

    for (vector<Game>::iterator iter = _container.begin(); iter != _container.end(); iter++)
    {
        xml_node<>* game_node = doc->allocate_node(node_element, "game");

        game_node->append_attribute(doc->allocate_attribute("team", iter->getTeam().getName().c_str() ));
        game_node->append_attribute(doc->allocate_attribute("opponent", iter->getOpponent().getName().c_str() ));
        game_node->append_attribute(doc->allocate_attribute("date", iter->getDate().c_str() ));
        game_node->append_attribute(doc->allocate_attribute("place", iter->getPlace().c_str() ));
        game_node->append_attribute(doc->allocate_attribute("viewers",  Functions::itoa(iter->getViewers()) ));
        game_node->append_attribute(doc->allocate_attribute("result", Functions::itoa(iter->getResult()) ));

        games_node->append_node(game_node);
    }

    return games_node;
}

void GameController::deserialize(xml_node<>* games_node)
{
    _container.clear();

    for (xml_node<>* game_node = games_node->first_node("game"); game_node; game_node = game_node->next_sibling())
    {
        Game game;

        game.setTeam( Team(game_node->first_attribute("team")->value()) );
        game.setOpponent( Team(game_node->first_attribute("opponent")->value()) );
        game.setDate( game_node->first_attribute("date")->value() );
        game.setPlace( game_node->first_attribute("place")->value() );
        game.setViewers( atoi(game_node->first_attribute("viewers")->value()) );
        game.setResult( atoi(game_node->first_attribute("result")->value()) );

        _container.push_back(game);
    }
}
