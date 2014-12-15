#include "DataBase.h"


DataBase::DataBase(void)
{
}


DataBase::~DataBase(void)
{
}


void DataBase::addPlayer(Player player)
{
	_player_controll.add( player );	
}

void DataBase::delPlayer(int id)
{
	_player_controll.del( id );
}

void DataBase::editPlayer(int id, string field, string value)
{
	_player_controll.edit( id, field, value );
}

Player* DataBase::getPlayer(int id)
{
	return _player_controll.searchById(id);
}

Player* DataBase::getPlayer(string name)
{
	return _player_controll.searchByName(name);
}

vector<Player> DataBase::getAllPlayers()
{
	return _player_controll.getContainer();
}



void DataBase::addGame(Game game)
{	
	Team* t = _team_controll.findByName( game.getTeam().getName() );
	Team* o = _team_controll.findByName( game.getOpponent().getName() );
	Team team;
	Team opponent;

	if (t != 0)
		team = *t;
	else
		team = Team( game.getTeam().getName() );	

	if (o != 0)
		opponent = *o;
	else
		opponent = Team( game.getOpponent().getName() );
	
	_game_controll.add( Game( team, opponent, game.getDate(), game.getPlace(), game.getViewers() ) );
}

void DataBase::delGame(int id)
{
	_game_controll.del( id );
}

void DataBase::editGame(int id, string field, string value)
{
	_game_controll.edit( id, field, value );
}

Game* DataBase::getGame(int id)
{
	return _game_controll.searchById(id);
}

Game* DataBase::getGameByDate(string date)
{
	return _game_controll.searchByDate(date);
}

Game* DataBase::getGameByOpponent(string opponent)
{
	return _game_controll.searchByOpponent(opponent);
}

vector<Game> DataBase::getAllGames()
{
	return _game_controll.getContainer();
}

void DataBase::sortGamesByDate()
{
	_game_controll.sortByDate();
}

void DataBase::sortGamesByResult()
{
	_game_controll.sortByResult();
}


void DataBase::addStadium(Stadium stadium)
{
	_stadium_controll.add( stadium );
}

void DataBase::delStadium(int id)
{
	_stadium_controll.del( id );
}

void DataBase::editStadium(int id, string field, string value)
{
	_stadium_controll.edit( id, field, value );
}

Stadium* DataBase::getStadium(int id)
{
	return _stadium_controll.searchById(id);	
}

Stadium* DataBase::getStadium(string name)
{
	return _stadium_controll.searchByName(name);
}

vector<Stadium> DataBase::getAllStadiums()
{
	return _stadium_controll.getContainer();
}


void DataBase::saveToFile()
{
    xml_document<> doc;
    std::ofstream file_stream( getDBFileName() );

    xml_node<>* head = doc.allocate_node(node_declaration);
    head->append_attribute(doc.allocate_attribute("version", "1.0"));
    head->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(head);

    xml_node<>* root = doc.allocate_node(node_element, "DataBase");
    root->append_attribute(doc.allocate_attribute("version", "1.0"));
    doc.append_node(root);

    root->append_node( _player_controll.serialize(&doc) );
    root->append_node( _game_controll.serialize(&doc) );
    root->append_node( _stadium_controll.serialize(&doc) );

    file_stream << doc;

    file_stream.close();
    doc.clear();
}

void DataBase::loadFromFile()
{
    xml_document<> doc;
    std::ifstream file_stream( getDBFileName() );

    if (!file_stream)
        return;

    vector<char> buffer = vector<char>(istreambuf_iterator<char>(file_stream), istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);
    xml_node<>* root_node = doc.first_node("DataBase");

    _player_controll.deserialize(root_node->first_node("players"));
    _game_controll.deserialize(root_node->first_node("games"));
    _stadium_controll.deserialize(root_node->first_node("stadiums"));
    // _team_controll.deserialize(root_node->first_node("teams"));

    file_stream.close();
    doc.clear();
}

string DataBase::getDBFileName()
{
    return "DataBase.xml";
}
