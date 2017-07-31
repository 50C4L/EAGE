#include "Module.h"

void Module::setName( std::string name )
{
	if( !name.empty() )	_name = name;
}

std::string Module::getName()
{
	if( _name.empty() )	_name = "Unnamed Module";
	return _name;
}