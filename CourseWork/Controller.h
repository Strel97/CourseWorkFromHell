#pragma once


#include <vector>
#include <string>

#include <RapidXml/rapidxml.hpp>


using std::vector;
using std::string;

using namespace rapidxml;

/**
 *
 */
template <class CType> class Controller
{
public:
    /**
     * @brief Controller
     */
    Controller()
    {

    }

    /**
     * @brief ~Controller
     */
    virtual ~Controller()
    {

    }

    /**
     * @brief add
     * @param node
     */
    void add(CType node)
    {
        _container.push_back( node );
    }

    /**
     * @brief del
     * @param node
     */
    void del(CType node)
    {
        for (typename vector<CType>::iterator iter = _container.begin(); iter != _container.end(); iter++)
            if (*iter == node)
                _container.erase(iter);
    }

    void del(int id)
    {
        if (validateID(id))
            _container.erase(_container.begin() + id);
    }    

    vector<CType> getContainer()
    {
        return _container;
    }

    bool validateID(int id)
    {
        return (id >= 0) && (id < _container.size());
    }

    virtual void edit(int id, string field, string value) = 0;

    virtual xml_node<>* serialize(xml_document<>* doc) = 0;
    virtual void deserialize(xml_node<>*) = 0;

protected:
	vector<CType> _container;
};

