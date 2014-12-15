#include "stadium.h"

Stadium::Stadium()
{
    _games = vector<Game>();
}

Stadium::Stadium(string name, int places, int ticket_price)
                    : _name(name), _places(places), _ticket_price(ticket_price)
{
    _games = vector<Game>();
}


void Stadium::setName(string name)
{
	_name = name;
}

void Stadium::setPlaces(int places)
{
    _places = places;
}

void Stadium::setTicketPrice(int ticket_price)
{
    _ticket_price = ticket_price;
}


string Stadium::getName()
{
    return _name;
}

int Stadium::getPlaces()
{
    return _places;
}

int Stadium::getTicketPrice()
{
    return _ticket_price;
}


bool Stadium::validateName(string name)
{
    return QRegExp("^[A-Z][a-z]+$").exactMatch(QString::fromStdString(name));
}

bool Stadium::validatePlaces(int places)
{
	return places > 0;
}

bool Stadium::validateTicketPrice(int ticket_price)
{
	return ticket_price > 0;
}

bool Stadium::validateModification(string field, string value)
{
	if (field == "NAME")
		validateName(value);
	else if (field == "PLACES")
		validatePlaces(stoi(value));
	else if (field == "TICKET_PRICE")
		validateTicketPrice( stoi(value) );

	return false;
}

void Stadium::addGame(Game game)
{
    _games.push_back(game);
}

void Stadium::delGame(Game game)
{
    for (int i = 0; i < _games.size(); i++)
        if (_games[i] == game)
            _games.erase(_games.begin() + i);
}


bool operator== (Stadium p1, Stadium p2)
{
    //if ((&p1 != 0) && (&p2 != 0))
    //{
	if ((p1._name == p2._name) &&
		(p1._places == p2._places) &&
		(p1._ticket_price == p2._ticket_price))
            return true;
    //}

    return false;
}

ostream& operator<<(ostream& os, const Stadium& stadium)
{
	os << setw(12) << stadium._name << setw(12) << stadium._places << setw(16) 
		<< stadium._ticket_price << endl;

    return os;
}
