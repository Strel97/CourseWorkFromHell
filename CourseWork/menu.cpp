#include "menu.h"

Menu::Menu()
{
    ErrDescription.push_back("Invalid Command! Use help!");
}

void Menu::start()
{
    showHelp();

    while(true)
    {
        string cmd = getCommand();
        parseCommand(cmd);
    }
}

string Menu::getCommand()
{
    cout << "# ";

    string buffer = string();
    getline(cin, buffer);    

    return buffer;
}

void Menu::parseCommand(string cmd)
{
    if (cmd == "help")
        showHelp();    

    else if (cmd == "add_player")
        addPlayer();
    else if (cmd == "del_player")
        delPlayer();
    else if (cmd == "modify_player")
        modifyPlayer();
    else if (cmd == "show_player")
        showPlayer();
    else if (cmd == "show_all_players")
        showAllPlayers();
	else if (cmd == "search_player")
		searchPlayer();

	else if (cmd == "add_game")
        addGame();
    else if (cmd == "del_game")
        delGame();
    else if (cmd == "modify_game")
        modifyGame();
	else if (cmd == "set_game_res")
		setGameResult();
    else if (cmd == "show_game")
        showGame();
    else if (cmd == "show_all_games")
        showAllGames();
	else if (cmd == "sort_games_by_date")
		sortGamesByDate();
	else if (cmd == "sort_games_by_res")
		sortGamesByResult();
	else if (cmd == "search_game_by_date")
		searchGameByDate();
	else if (cmd == "search_game_by_opponent")
		searchGameByOpponent();

	else if (cmd == "add_stadium")
        addStadium();
    else if (cmd == "del_stadium")
        delStadium();
    else if (cmd == "modify_stadium")
        modifyStadium();			
    else if (cmd == "show_stadium")
        showStadium();
    else if (cmd == "show_all_stadiums")
        showAllStadiums();
	else if (cmd == "search_stadium")
		searchStadium();

    else if (cmd == "save_db")
        saveDbToFile();
    else if (cmd == "load_db")
        loadDbFromFile();

    else if (cmd == "")
        {}
    else if (cmd == "exit")
        exit(0);
    else
        error(ERR_INVALID_CMD);
}

void Menu::showHelp()
{
	cout << setw(30) << right << "[=== HELP ===]" << endl << endl;
	
	cout << "Operations with Players:" << endl;
	cout << left << setw(30) << "-[ add_player "		<< "Adds new player to DataBase." << endl;
	cout << left << setw(30) << "-[ del_player "		<< "Deletes player from DataBase." << endl;
	cout << left << setw(30) << "-[ modify_player "		<< "Modifies player information in DataBase." << endl;
	cout << left << setw(30) << "-[ show_player "		<< "Shows player from DataBase." << endl;
	cout << left << setw(30) << "-[ show_all_player "	<< "Shows all players from DataBase." << endl;
	cout << left << setw(30) << "-[ search_player "		<< "Searches player in DataBase by name." << endl;
	cout << endl;

	cout << "Operations with Games:" << endl;
	cout << left << setw(30) << "-[ add_game "					<< "Adds new game to DataBase." << endl;
	cout << left << setw(30) << "-[ del_game "					<< "Deletes game from DataBase." << endl;
	cout << left << setw(30) << "-[ modify_game "				<< "Modifies game's information in DataBase." << endl;
	cout << left << setw(30) << "-[ set_game_res "				<< "Sets game's result information in DataBase." << endl;
	cout << left << setw(30) << "-[ show_game "					<< "Shows game from DataBase." << endl;
	cout << left << setw(30) << "-[ show_all_games "			<< "Shows all games from DataBase." << endl;
	cout << left << setw(30) << "-[ sort_games_by_date "		<< "Sorts all games in DataBase by date." << endl;
	cout << left << setw(30) << "-[ sort_games_by_res "			<< "Sorts all games in DataBase by result." << endl;
	cout << left << setw(30) << "-[ search_game_by_date "		<< "Searches game in DataBase by date." << endl;
	cout << left << setw(30) << "-[ search_game_by_opponent "	<< "Searches game in DataBase by opponent team name." << endl;
	cout << endl;

	cout << "Operations with Stadiums:" << endl;
	cout << left << setw(30) << "-[ add_stadium "		<< "Adds new stadium to DataBase." << endl;
	cout << left << setw(30) << "-[ del_stadium "		<< "Deletes stadium from DataBase." << endl;
	cout << left << setw(30) << "-[ modify_stadium "	<< "Modifies stadium information in DataBase." << endl;
	cout << left << setw(30) << "-[ show_stadium "		<< "Shows stadium from DataBase." << endl;
	cout << left << setw(30) << "-[ show_all_stadiums "	<< "Shows all stadiums from DataBase." << endl;
	cout << left << setw(30) << "-[ search_stadium "	<< "Searches stadium in DataBase by name." << endl;
    cout << endl;

    cout << "Operations with DB:" << endl;
    cout << left << setw(30) << "-[ save_db "           << "Saves db in xml file." << endl;
    cout << left << setw(30) << "-[ load_db "           << "Loads db from xml file." << endl;
	cout << endl;

}

void Menu::error(int code)
{
    cout << "ERROR #" << code << ": " << ErrDescription[code] << endl;
}

// === Player Section ===
void Menu::addPlayer()
{
    string  name = "";
    string  surname = "";
    string  birthday = "";
    string  status = "";
    string  health = "";
    int     salary = -1;

    cout << "[=== Player Addition ===]" << endl;

    while(!Player::validateName(name))
    {
        cout << "-[ Name: ";
        cin >> name;
    }

    while(!Player::validateSurname(surname))
    {
        cout << "-[ Surname: ";
        cin >> surname;
    }

    while(!Player::validateBirthday(birthday))
    {
        cout << "-[ Birthday: ";
        cin >> birthday;
    }

    while(!Player::validateStatus(status))
    {
        cout << "-[ Status: ";
        cin >> status;
    }

    while(!Player::validateHealth(health))
    {
        cout << "-[ Health: ";
        cin >> health;
    }

    while(!Player::validateSalary(salary))
    {
        cout << "-[ Salary: ";
        cin >> salary;
    }
    cout << endl;

	database.addPlayer( Player(name, surname, birthday, status, health, salary) );
}

void Menu::delPlayer()
{
    int id;

    showAllPlayers();

    cout << "[=== Player Deletion ===]" << endl;
    cout << "-[ PlayerID: ";    cin >> id;
    cout << endl;

    database.delPlayer( id );
}

void Menu::modifyPlayer()
{
    int id;
    string field;
    string value;

    showAllPlayers();

    cout << "[=== Player Edition ===]" << endl;
    cout << "-[ PlayerID: ";    cin >> id;
    cout << endl;

	while(!Player::validateModification(field, value))
	{		
		cout << "Which field you want to modify? => ";		cin >> field;
		cout << "Value: ";									cin >> value;
	}
	cout << endl;

    database.editPlayer(id, field, value);
}

void Menu::showPlayer()
{
    int id;

    showAllPlayers();

    cout << "PlayerID: ";   cin >> id;
    Player* player = database.getPlayer(id);

	if (player != 0)
		cout << *player;
}

void Menu::showAllPlayers()
{
    vector<Player> players = database.getAllPlayers();

	cout << setw(45) << right << "[=== Player's DataBase ===]" << endl;
    cout << "[ID]" << setw(10) << "[NAME]" << setw(12) << "[SURNAME]" << setw(12) << "[BIRTHDAY]" << setw(12) << 
		"[STATUS]" << setw(12) << "[HEALTH]" << setw(12) << "[SALARY]" << endl;
	for (int i = 0; i < players.size(); i++)
		cout << i << setw(12) << players[i];

    cout << endl;
}

void Menu::searchPlayer()
{
	string name;

	cout << "[=== Player Searching ===]" << endl;
    while(!Player::validateName(name))
    {
        cout << "-[ Name: ";
        cin >> name;
    }

	Player* player = database.getPlayer(name);
	if (player != 0)
		cout << *player;
}
// ====================

// === Game Section ===
void Menu::addGame()
{
    string  team;
    string  opponent;
    string  date;
    string  place;
    int     viewers = -1;

    cout << "[=== Player Addition ===]" << endl;

    while(!Team::validateName(team))
    {
        cout << "-[ Team Name: ";
        cin >> team;
    }

	while(!Team::validateName(opponent))
    {
        cout << "-[ Opponent team Name: ";
        cin >> opponent;
    }

    while(!Game::validateDate(date))
    {
        cout << "-[ Date: ";
        cin >> date;
    }

    while(!Stadium::validateName(place))
    {
        cout << "-[ Place: ";
        cin >> place;
    }

	while(!Game::validateViewers(viewers))
    {
        cout << "-[ Viewers: ";
		cin >> viewers;
    }
    cout << endl;

	database.addGame( Game(team, opponent, date, place, viewers) );
}

void Menu::delGame()
{
    int id;

    showAllGames();

    cout << "[=== Game Deletion ===]" << endl;
    cout << "-[ GameID: ";    cin >> id;
    cout << endl;

    database.delGame( id );
}

void Menu::modifyGame()
{
    int id;
    string field;
    string value;

    showAllGames();

	cout << "[=== Game Edition ===]" << endl;
    cout << "-[ GameID: ";		cin >> id;
    cout << endl;

	while(!Game::validateModification(field, value))
	{		
		cout << "Which field you want to modify? => ";		cin >> field;
		cout << "Value: ";									cin >> value;
	}
	cout << endl;

	database.editGame(id, field, value);
}

void Menu::setGameResult()
{
	int id;
    string result;

    showAllGames();
	
	cout << "[=== Game Edition ===]" << endl;
    cout << "-[ GameID: ";		cin >> id;
    cout << endl;

	while (!Game::validateResult(stoi(result)))
	{
		cout << "-[ Game Result: ";		
		cin >> result;
	}

	database.editGame(id, "RESULT", result);
}

void Menu::showGame()
{
    int id;

    showAllGames();

    cout << "GameID: ";   cin >> id;
    Game* game = database.getGame(id);

	if (game != 0)
		cout << game;
}

void Menu::showAllGames()
{
    vector<Game> games = database.getAllGames();

	cout << setw(45) << "[=== Game's DataBase ===]" << endl;
    cout << setw(10) << left << "[ID]" << setw(12) << "[TEAM]" << setw(18) << "[OPPONENT]" << setw(12) << "[DATE]" << setw(12) << 
		"[PLACE]" << setw(12) << "[VIEWERS]" << endl;
	for (int i = 0; i < games.size(); i++)
        cout << setw(12) << i << games[i];

    cout << endl;
}

void Menu::sortGamesByDate()
{
	database.sortGamesByDate();

	showAllGames();
}

void Menu::sortGamesByResult()
{
	database.sortGamesByResult();

	showAllGames();
}

void Menu::searchGameByDate()
{
	string date;

	cout << "[=== Game Searching ===]" << endl;
	while(!Game::validateDate(date))
    {
        cout << "-[ Date: ";
        cin >> date;
    }

	Game* game = database.getGameByDate(date);
	if (game != 0)
		cout << *game;
}

void Menu::searchGameByOpponent()
{
	string opponent;

	cout << "[=== Game Searching ===]" << endl;
	while(!Team::validateName(opponent))
    {
        cout << "-[ Opponent team Name: ";
		cin >> opponent;
    }

	Game* game = database.getGameByOpponent(opponent);
	if (game != 0)
		cout << *game;
}
// =========================


// === Stadium's section ===
void Menu::addStadium()
{
	string name;
	int places = 0;
	int ticket_price = 0;

    cout << "[=== Stadium Addition ===]" << endl;

	while(!Stadium::validateName(name))
    {
        cout << "-[ Name: ";
        cin >> name;
    }

	while(!Stadium::validatePlaces(places))
    {
        cout << "-[ Places: ";
		cin >> places;
    }

	while(!Stadium::validateTicketPrice(ticket_price))
    {
        cout << "-[ TicketPrice: ";
		cin >> ticket_price;
    }
	cout << endl;

	database.addStadium( Stadium(name, places, ticket_price) );
}

void Menu::delStadium()
{
	int id;

	showAllStadiums();

    cout << "[=== Stadium Deletion ===]" << endl;
    cout << "-[ StadiumID: ";    cin >> id;
    cout << endl;

	database.delStadium( id );
}

void Menu::modifyStadium()
{
	int id;
    string field;
    string value;

	showAllStadiums();

	cout << "[=== Stadium Edition ===]" << endl;
    cout << "-[ StadiumID: ";		cin >> id;
    cout << endl;

	while(!Stadium::validateModification(field, value))
	{		
		cout << "Which field you want to modify? => ";		cin >> field;
		cout << "Value: ";									cin >> value;
	}
	cout << endl;

	database.editStadium(id, field, value);
}

void Menu::showStadium()
{
	int id;

	showAllStadiums();

    cout << "StadiumID: ";   cin >> id;
	Stadium* stadium = database.getStadium(id);

	if (stadium != 0)
		cout << stadium;
}

void Menu::showAllStadiums()
{
	vector<Stadium> stadiums = database.getAllStadiums();

	cout << setw(35) << right << "[=== Stadium's DataBase ===]" << endl;
    cout << "[ID]" << setw(10) << "[NAME]" << setw(12) << "[PLACES]" << setw(18) << "[TICKET_PRICE]" << endl;
	for (int i = 0; i < stadiums.size(); i++)
		cout << i << setw(12) << stadiums[i];
    cout << endl;
}

void Menu::searchStadium()
{
	string name;

	cout << "[=== Stadium Searching ===]" << endl;
	while(!Stadium::validateName(name))
    {
        cout << "-[ Name: ";
        cin >> name;
    }

	Stadium* stadium = database.getStadium(name);
	if (stadium != 0)
		cout << *stadium;
}
// ==========================


void Menu::saveDbToFile()
{
    database.saveToFile();
}

void Menu::loadDbFromFile()
{
    database.loadFromFile();
}
