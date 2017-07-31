#include "helper.h"

SkeletonNode::SkeletonNode()
{
	_parent = 0;
	_childCount = 0;
	_attCount = 0;
	_id = -1;
}


SkeletonNode::~SkeletonNode()
{
	clear();
}


sf::Vector2f SkeletonNode::getPosition()
{
	return _position;

}


void SkeletonNode::setPosition( sf::Vector2f pos )
{
	_position = pos;
}


void SkeletonNode::clear()
{
	if( !_childList.empty() )
	{
		_childList.clear();
		_childCount = 0;
	}
	if( !_attachment.empty() )
	{
		_attachment.clear();
		_attCount = 0;
	}
}


void SkeletonNode::attach( GameObject* obj )
{
	if( obj && _attCount < MAX_NODE_ATTACHMENT_NUMBER )
	{
		_attachment.push_back(obj);
		_attCount++;
	}
}


void SkeletonNode::translate( sf::Vector2f direction )
{
	_position += direction;
	// if have child
	if( _childCount > 0 )
	{
		for( int i = 0; i < _childCount; i++ )
		{
			_childList[i]->translate( direction );
		}
	}

	// if have attachment
	if( _attCount > 0 )
	{
		for( int i = 0; i < _attCount; i++ )
		{
			_attachment[i]->setTranslate( direction );
		}
	}
}


void SkeletonNode::rotate( sf::Vector2f center, float angle )
{
	sf::Transform transform = sf::Transform::Identity;
	transform.rotate( angle, center );
	_position = transform * _position;

	// if have child
	if( _childCount > 0 )
	{
		for( int i = 0; i < _childCount; i++ )
		{
			_childList[i]->rotate( transform );
		}
	}

	// if have attachment
	if( _attCount > 0 )
	{
		for( int i = 0; i < _attCount; i++ )
		{
			_attachment[i]->setRotate( angle, center );
		}
	}
}


void SkeletonNode::rotate( sf::Transform trans )
{
	_position = trans * _position;

	// if have child
	if( _childCount > 0 )
	{
		for( int i = 0; i < _childCount; i++ )
		{
			_childList[i]->rotate( trans );
		}
	}

	// if have attachment
	if( _attCount > 0 )
	{
		for( int i = 0; i < _attCount; i++ )
		{
			_attachment[i]->setRotate( trans );
		}
	}
}


void SkeletonNode::rotateArroundParent( float angle )
{
	if( _parent )
	{
		sf::Transform transform = sf::Transform::Identity;
		transform.rotate( angle, _parent->getPosition() );
		_position = transform * _position;

		// if have child
		if( _childCount > 0 )
		{
			for( int i = 0; i < _childCount; i++ )
			{
				_childList[i]->rotate( transform );
			}
		}

		// if have attachment
		if( _attCount > 0 )
		{
			for( int i = 0; i < _attCount; i++ )
			{
				_attachment[i]->setRotate( transform );
			}
		}
	}
	else
	{
		sf::Transform transform = sf::Transform::Identity;
		transform.rotate( angle, _position );
		_position = transform * _position;

		// if have child
		if( _childCount > 0 )
		{
			for( int i = 0; i < _childCount; i++ )
			{
				_childList[i]->rotate( transform );
			}
		}

		// if have attachment
		if( _attCount > 0 )
		{
			for( int i = 0; i < _attCount; i++ )
			{
				_attachment[i]->setRotate( transform );
			}
		}
	}
}


void SkeletonNode::setParent( SkeletonNode* par )
{
	if( par )
		_parent = par;
}


bool SkeletonNode::addNode( SkeletonNode* node )
{
	/*if( !_child )
		_child = new SkeletonNode[MAX_NODES_NUMBER];

	if( _childCount < MAX_NODES_NUMBER )
	{
		_child[_childCount] = node;
		_child[_childCount].setParent( this );
		_childCount++;

		return true;
	}*/
	if( node )
	{
		if( _childCount < MAX_NODES_NUMBER )
		{
			_childList.push_back( node );
			_childCount++;
			return true;
		}
	}

	return false;
}


SkeletonNode* SkeletonNode::addNode( int id, sf::Vector2f pos )
{
	if( id > -1 )
	{
		SkeletonNode *temp = new SkeletonNode();
		temp->setId( id );
		temp->setPosition( pos );

		if( _childCount < MAX_NODES_NUMBER )
		{
			_childList.push_back( temp );
			_childCount++;
			return temp;
		}
	}

	return 0;
}


void SkeletonNode::setId( int id )
{
	_id = id;
}


int SkeletonNode::getId()
{
	return _id;
}



SkeletonNode* SkeletonNode::search( int id )
{
	SkeletonNode* temp;
	// if have child
	if( _childCount > 0 )
	{
		for( int i = 0; i < _childCount; i++ )
		{
			if( _childList[i]->getId() == id  )
				return _childList[i];
			else 
			{
				temp = _childList[i]->search(id);
				return (temp!=0?temp:0);
			}
		}
	}

	return 0;
}
