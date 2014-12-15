#include "team.h"


// === CODE ERRORS ===
// - It works!
// ===================

// === Constructors ===
Team::Team()
{
    _team = vector<Player>();
}

Team::Team(string name)
{
    _name = name;
    _team = vector<Player>();
}

Team::Team(string name, vector<Player> team)
{
    _name = name;
    _team = team;
}
// =====================


// === Getters And Setters ===
string Team::getName()
{
    return _name;
}

void Team::setName(string name)
{
    _name = name;
}
// ===========================


// === Methods ===
void Team::addPlayer(Player player)
{
    if (!isFull())
        _team.push_back(player);
}

void Team::delPlayer(Player player)
{
    if (isEmpty())
        return;

    for (int i = 0; i < _team.size(); i++)
        if (_team[i] == player)
            _team.erase(_team.begin() + i);
}

bool Team::isFull()
{
    return _team.size() == PLAYER_CNT;
}

bool Team::isEmpty()
{
    return _team.empty();
}

bool Team::validateName(string name)
{
    return QRegExp("^[A-Z][a-z]+$").exactMatch(QString::fromStdString(name));
}

void Team::to_console()
{
    cout << "=== Team " << _name << " Output ===" << endl;
    for (vector<Player>::iterator iter = _team.begin(); iter != _team.end(); ++iter)
    {
        Player p = *iter;
        cout << p << endl;
    }
    cout << endl;
}
// ====================


bool operator== (Team t1, Team t2)
{
    //if ((&t1 != 0) && (&t2 != 0))
    //{
        if ((t1._name == t2._name) &&
                (t1._team == t2._team))
            return true;
    //}

    return false;
}

ostream& operator<<(ostream& os, const Team& team)
{
	os << team._name;

    return os;
}
