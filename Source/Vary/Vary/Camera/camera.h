#ifndef CAMERA_H
#define CAMERA_H

#include "../Entities/hero.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>


class Camera
{
public:
	explicit				Camera(const sf::View &view);
							Camera(const Camera &) = delete;
	Camera &				operator=(const Camera &) = delete;

	sf::View &				getView();
	sf::FloatRect			getViewBounds() const;

	void					setHero(Hero *hero);

	void					update(sf::FloatRect worldBounds);


private:
	void					correctPosition(sf::FloatRect worldBounds);


private:
	sf::View				mView;
	Hero					*mHero;
};

#endif
