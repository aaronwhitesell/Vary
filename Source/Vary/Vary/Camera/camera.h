#ifndef CAMERA_H
#define CAMERA_H

#include "../Entities/hero.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>


class Camera
{
public:
							Camera(const sf::View &view, sf::FloatRect worldBounds);
							Camera(const Camera &) = delete;
	Camera &				operator=(const Camera &) = delete;

	sf::View &				getView();
	sf::FloatRect			getViewBounds() const;

	void					setHero(Hero *hero);

	void					update();


private:
	void					correctPosition();


private:
	sf::View				mView;
	Hero					*mHero;
	sf::FloatRect			mWorldBounds;
};

#endif
