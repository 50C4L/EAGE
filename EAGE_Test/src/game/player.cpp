#include "player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::move( sf::Vector2f dir, float speed )
{
	this->setLinearVelocity( dir.x*speed, dir.y*speed );
}

void Player::stop()
{
	this->setLinearVelocity( 0.f, 0.f );
}

void Player::react()
{
	this->setTranslate( this->getHistory() * (-1.0f) );
}