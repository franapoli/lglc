/*
 * Node.h
 *
 *  Created on: 01/apr/2010
 *      Author: ciccio
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include "Linkable.h"

using namespace std;

class Node : public Linkable {
	friend class Edge;
	friend class Graph;
public:
	Node();
	Node(string name);
	virtual ~Node();


    bool isVisited(void) {return _visited;}

    void Visit(void);
    bool isSink() const
    {
        return _issink;
    }

    bool isSource() const
    {
        return _issource;
    }


    unsigned getId() {return _id;}

    ostream& operator>>(std::ostream &);
    Edgeset &GetEdges(void);
    string getInConnector() const
    {
    		return _inconnector;
    }

    string getOutConnector() const
    {
    		return _outconnector;
    }

    void setInConnector(string _inconn)
    {
        _inconnector = _inconn;
    }

    void setOutConnector(string _outconn)
    {
        _outconnector = _outconn;
    }

    bool getIsinput() const
    {
        return _isinput;
    }

    bool getIsoutput() const
    {
        return _isoutput;
    }

    void setIsinput(bool _isinput)
    {
        this->_isinput = _isinput;
    }

    void setIsoutput(bool _isoutput)
    {
        this->_isoutput = _isoutput;
    }
	virtual Linkable &Clone(){Node &n=*new Node; n=*this; return n;}

	unsigned static newId(){return _lastid++;}

	void setId(unsigned i){_id =i;}
	void UpdateIds(){setId(newId());}
	void SetAttribute(std::string s1, std::string s2) {_attributes[s1]=s2;}

private:
	void SetAttribute(unsigned, std::string s1, std::string s2){_attributes[s1]=s2;};
	inline Nodeset& GetOutputs(void);
	inline Nodeset& GetInputs(void);
	inline Nodeset& GetNodes(void);
	inline void SetInputs(Nodeset &);
	inline void SetOutputs(Nodeset &);
	inline Nodeset& GetSources(void);
	inline Nodeset& GetSinks(void);

	bool			_visited;
	unsigned		_id;
	static unsigned	_lastid;
	bool			_issink;
	bool			_issource;
	bool			_isinput;
	bool			_isoutput;
	std::string 	_inconnector;
	std::string 	_outconnector;

};

#endif /* NODE_H_ */
