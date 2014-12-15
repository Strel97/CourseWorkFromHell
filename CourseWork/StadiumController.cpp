#include "StadiumController.h"


StadiumController::StadiumController(void)
{
	_container.push_back( Stadium("Ret", 12, 123) );
	_container.push_back( Stadium("Per", 13, 113) );
	_container.push_back( Stadium("Ads", 14, 103) );
	_container.push_back( Stadium("Fsa", 15, 193) );
	_container.push_back( Stadium("Kdt", 16, 183) );
}


StadiumController::~StadiumController(void)
{
}

void StadiumController::edit(int id, string field, string value)
{
	if (validateID(id))
	{
		Stadium stadium = _container[id];
		
		if (field == "NAME")
			stadium.setName(value);
		else if (field == "PLACES")
			stadium.setPlaces(stoi(value));
		else if (field == "TICKET_PRICE")
			stadium.setTicketPrice(stoi(value));
		
		_container[id] = stadium;
	}
}

Stadium* StadiumController::searchById(int id)
{
	if (validateID(id))					
		return &_container[id];

	return 0;
}

Stadium* StadiumController::searchByName(string name)
{
	for (int i = 0; i < _container.size(); i++)
		if (_container[i].getName() == name)
			return &_container[i];

	return 0;
}

xml_node<>* StadiumController::serialize(xml_document<>* doc)
{
    xml_node<>* stadiums_node = doc->allocate_node(node_element, "stadiums");    
    stadiums_node->append_attribute(doc->allocate_attribute("size", Functions::itoa( _container.size() )));

    for (vector<Stadium>::iterator iter = _container.begin(); iter != _container.end(); iter++)
    {
        xml_node<>* stadium_node = doc->allocate_node(node_element, "stadium");

        stadium_node->append_attribute(doc->allocate_attribute("name", iter->getName().c_str() ));
        stadium_node->append_attribute(doc->allocate_attribute("places", Functions::itoa( iter->getPlaces() )));
        stadium_node->append_attribute(doc->allocate_attribute("ticket_price", Functions::itoa( iter->getTicketPrice() )));

        stadiums_node->append_node(stadium_node);
    }

    return stadiums_node;
}

void StadiumController::deserialize(xml_node<>* stadiums_node)
{
    _container.clear();

    for (xml_node<>* stadium_node = stadiums_node->first_node("stadium"); stadium_node; stadium_node = stadium_node->next_sibling())
    {
        Stadium stadium;

        stadium.setName( stadium_node->first_attribute("name")->value() );
        stadium.setPlaces( atoi( stadium_node->first_attribute("places")->value() ));
        stadium.setTicketPrice( atoi( stadium_node->first_attribute("ticket_price")->value() ));

        _container.push_back(stadium);
    }
}
