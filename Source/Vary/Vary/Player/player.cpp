#include "player.h"

#include <SFML/Window/Event.hpp>


Player::Player()
: mController()
{
}

const Controller & Player::getController() const
{
	return mController;
}

Controller & Player::getController()
{
	return mController;
}

void Player::update()
{
	mController.update();
}

void Player::handleEvent(const sf::Event &inputEvent)
{
	mController.handleEvent(inputEvent);
}
