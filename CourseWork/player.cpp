#include "player.h"


// === CODE ERRORS ===
// - It works!
// ===================


// === Constructors ===
Player::Player()
{
}

Player::Player(string name, string surname, string birthday, string status, string health, int salary)
    : _name(name), _surname(surname), _birthday(birthday), _status(status), _health(health), _salary(salary)
{
}
/*
Player::Player(int id, string name, string surname, string birthday, string status, string health, int salary)
    : _id(id), _name(name), _surname(surname), _birthday(birthday), _status(status), _health(health), _salary(salary)
{
}
*/
// ====================


// === Getters ===
/*
int Player::getID()
{
	return _id;
}
*/
string Player::getName()
{
    return _name;
}

string Player::getSurname()
{
    return _surname;
}

string Player::getBirthday()
{
    return _birthday;
}

string Player::getStatus()
{
    return _status;
}

string Player::getHealth()
{
    return _health;
}

int Player::getSalary()
{
    return _salary;
}
// ===============


// === Setters ===
/*void Player::setID(int id)
{
	_id = id;
}
*/
void Player::setName(string name)
{
    _name = name;
}

void Player::setSurname(string surname)
{
    _surname = surname;
}

void Player::setBirthday(string birthday)
{
	_birthday = birthday;
}

void Player::setStatus(string status)
{
    _status = status;
}

void Player::setHealth(string health)
{
    _health = health;
}

void Player::setSalary(int salary)
{
    _salary = salary;
}
// ===============


// === Methods ===
bool Player::validateName(string name)
{
    return QRegExp("^[A-Z][a-z]+$").exactMatch(QString::fromStdString(name));
}

bool Player::validateSurname(string surname)
{
    return QRegExp("^[A-Z][a-z]+$").exactMatch(QString::fromStdString(surname));
}

bool Player::validateBirthday(string birthday)
{
    return QRegExp("[0-9]{2}.[0-9]{2}.[0-9]{4}").exactMatch(QString::fromStdString(birthday));
}

bool Player::validateStatus(string status)
{
    return QRegExp("(ATTACK)|(DEFENCE)|(GOALKEEPER)").exactMatch(QString::fromStdString(status));
}

bool Player::validateHealth(string health)
{
    return QRegExp("(HEALTHY)|(SICK)").exactMatch(QString::fromStdString(health));
}

bool Player::validateSalary(int salary)
{
    return (salary > 0) && (salary < 10000);
}

bool Player::validateModification(string field, string value)
{
	if (field == "NAME")
		return validateName(value);
	else if (field == "SURNAME")
		return validateSurname(value);
	else if (field == "BIRTHDAY")
		return validateBirthday(value);
	else if (field == "STATUS")
		return validateStatus(value);
	else if (field == "HEALTH")
		return validateHealth(value);
	else if (field == "SALARY")
		return validateSalary(stoi(value));

	return false;
}
// ===============


// === Operators ===
bool operator== (Player p1, Player p2)
{
    //if ((&p1 != 0) && (&p2 != 0))
    //{
        if ((p1._name == p2._name) &&
                (p1._surname == p2._surname) &&
                    (p1._birthday == p2._birthday) &&
                        (p1._status == p2._status) &&
                            (p1._health == p2._health) &&
                                (p1._salary == p2._salary))
            return true;
    //}

    return false;
}

ostream& operator<<(ostream& os, const Player& player)
{
	os << player._name << setw(9) << player._surname << setw(16) 
		<< player._birthday << setw(12) << player._status << setw(12) << player._health << setw(12) << player._salary << endl;

    return os;
}
// =================
