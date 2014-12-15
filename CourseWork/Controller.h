#pragma once


#include <vector>
#include <string>

#include <RapidXml/rapidxml.hpp>


using std::vector;
using std::string;

using namespace rapidxml;

/**
 *  This template class represents the controller
 *  in MVC pattern. It has basic operations for
 *  adding and deleting element of any type to or from
 *  collection.
 */
template <class CType> class Controller
{
public:
    /**
     * @brief Controller    Creates empty controller
     */
    Controller()
    {

    }

    /**
     * @brief ~Controller   Seek And Destroy!!!
     */
    virtual ~Controller()
    {

    }

    /**
     * @brief add       Adds element to the collection
     * @param node      Element to be added
     */
    void add(CType node)
    {
        _container.push_back( node );
    }

    /**
     * @brief del       Deletes specified element from collection
     * @param node      Element info for deleting
     */
    void del(CType node)
    {
        for (typename vector<CType>::iterator iter = _container.begin(); iter != _container.end(); iter++)
            if (*iter == node)
                _container.erase(iter);
    }

    /**
     * @brief del   Deletes element from collection by specified id
     * @param id    ID of element in collection
     */
    void del(int id)
    {
        if (validateID(id))
            _container.erase(_container.begin() + id);
    }    

    /**
     * @brief getContainer  Returns the list of objects (or collection)
     * @return              Collection of objects
     */
    vector<CType> getContainer()
    {
        return _container;
    }

    /**
     * @brief validateID    Validates  the value of ID
     * @param id            ID of object
     * @return              Wheter id meets the following conditions
     *
     * ID must be greater or equal to zero and less than collection
     * size to predict out of range exception
     */
    bool validateID(int id)
    {
        return (id >= 0) && (id < _container.size());
    }

    /**
     * @brief edit      Edits the content of object
     * @param id        ID of object in collection
     * @param field     Field to modify
     * @param value     New value of field
     *
     * Each controller class implements this method and realizes it
     * because each class has it's own fields and allowable values for them
     */
    virtual void edit(int id, string field, string value) = 0;

    /**
     * @brief serialize Creates the xml_node object for further serialization
     * @param doc       Reference to xml document
     * @return          xml_node, the content of collection
     */
    virtual xml_node<>* serialize(xml_document<>* doc) = 0;

    /**
     * @brief deserialize   Pass information from xml file and creates objects
     * on the base of this information
     */
    virtual void deserialize(xml_node<>*) = 0;

protected:
    /**
     * @brief _container    Collection of objects
     */
	vector<CType> _container;
};

