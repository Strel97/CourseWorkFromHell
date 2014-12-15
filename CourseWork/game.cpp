#include "game.h"

Game::Game()
{
}

Game::Game(string team, string opponent, string date, string place, int viewers)
				: _date(date), _place(place), _viewers(viewers)
{
	_team = Team(team);
	_opponent = Team(opponent);
	_result = GameResults::NOT_PLAYED;
}

Game::Game(Team team, Team opponent, string date, string place, int viewers)
            : _team(team), _opponent(opponent), _date(date), _place(place), _viewers(viewers)
{
	_result = GameResults::NOT_PLAYED;
}

/*
void Game::setID(int id)
{
	_id = id;
}
*/
void Game::setTeam(Team team)
{
	_team = team;
}

void Game::setOpponent(Team opponent)
{
	_opponent = opponent;
}

void Game::setDate(string date)
{
    _date = date;
}

void Game::setPlace(string place)
{
    _place = place;
}

void Game::setViewers(int viewers)
{
    _viewers = viewers;
}

void Game::setResult(int result)
{
    _result = result;
}

/*
int Game::getID()
{
	return _id;
}
*/
Team Game::getTeam()
{
	return _team;
}

Team Game::getOpponent()
{
	return _opponent;
}

string Game::getDate()
{
	return _date;
}

string Game::getPlace()
{
	return _place;
}

int Game::getViewers()
{
	return _viewers;
}

int Game::getResult()
{
    return _result;
}


bool Game::validateDate(string date)
{
    return QRegExp("[0-9]{2}.[0-9]{2}.[0-9]{4}").exactMatch(QString::fromStdString(date));
}

bool Game::validateViewers(int viewers)
{
	return (viewers >= 0) && (viewers <= 100);	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool Game::validateResult(int result)
{
	return (result >= GameResults::WIN) && (result <= GameResults::NOT_PLAYED);
}

bool Game::validateModification(string field, string value)
{
	if (field == "TEAM")
		return Team::validateName(value);
	else if (field == "OPPONENT")
		return Team::validateName(value);
	else if (field == "DATE")
		return validateDate(value);
	else if (field == "PLACE")
		return Team::validateName(value);
	else if (field == "VIEWERS")
		return validateViewers(stoi(value));

	return false;
}


bool operator== (Game g1, Game g2)
{
    //if ((&g1 != 0) && (&g2 != 0))
    //{
        if ((g1._team == g2._team) &&
                (g1._opponent == g2._opponent) &&
                    (g1._date == g2._date) &&
                        (g1._place == g2._place) &&
                            (g1._result == g2._result))
            return true;
    //}

    return false;
}

ostream& operator<<(ostream& os, const Game& game)
{
	os << setw(12) << game._team << setw(12) << game._opponent << setw(16) 
		<< game._date << setw(12) << game._place << setw(16) << game._viewers << endl;

    return os;
}
