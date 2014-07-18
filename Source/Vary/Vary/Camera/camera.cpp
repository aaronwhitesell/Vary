#include "camera.h"

#include <SFML/System/Vector2.hpp>

#include <algorithm>


Camera::Camera(const sf::View &view, sf::FloatRect worldBounds)
: mView(view)
, mHero(nullptr)
, mWorldBounds(worldBounds)
{
}

sf::View & Camera::getView()
{
	return mView;
}

void Camera::setHero(Hero *hero)
{
	mHero = hero;
}

void Camera::update()
{
	mView.setCenter(mHero->getPosition()); // ALW - Center camera over hero
	correctPosition();					   // ALW - Correct camera position, if is outside world
}

void Camera::correctPosition()
{
	// ALW - If the camera moves outside the boundaries of the world then
	// ALW - move it back to the world boundary.
	sf::Vector2f position = mView.getCenter();
	sf::FloatRect viewBounds = getViewBounds();
	
	sf::Vector2f viewHalfDimensions; // ALW - Account for the camera's position being the center
	viewHalfDimensions.x = viewBounds.width / 2.0f;
	viewHalfDimensions.y = viewBounds.height / 2.0f;

	position.x = std::max(position.x, mWorldBounds.left + viewHalfDimensions.x);
	position.x = std::min(position.x, mWorldBounds.left + mWorldBounds.width - viewHalfDimensions.x);
	position.y = std::max(position.y, mWorldBounds.top + viewHalfDimensions.y);
	position.y = std::min(position.y, mWorldBounds.top + mWorldBounds.height - viewHalfDimensions.y);
	
	mView.setCenter(position);
}

sf::FloatRect Camera::getViewBounds() const
{
	return sf::FloatRect(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());
}



