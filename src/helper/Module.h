#ifndef _MODULE_H
#define _MODULE_H

#include <string>

class Module
{
public:
	//virtual	bool	initialize() = 0;
	virtual	void	shutdown() = 0;
	virtual void	setName( std::string name );

	std::string getName();

private:
	std::string	_name;
};

#endif _MODULE_H