#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>


class Camera
{
public:
							Camera(const sf::View &view, sf::FloatRect worldBounds);
							Camera(const Camera &) = delete;
	Camera &				operator=(const Camera &) = delete;

	sf::View &				getView();
	sf::FloatRect			getViewBounds() const;

	void					update(sf::Vector2f position);


private:
	void					correctPosition();


private:
	sf::View				mView;
	sf::FloatRect			mWorldBounds;
};

#endif
