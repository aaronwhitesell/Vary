#ifndef WORLD_H
#define WORLD_H

#include "Trambo/Resources/resourceHolder.h"
#include "Trambo/SceneNodes/sceneNode.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>

#include <array>


namespace sf
{
	class RenderTarget;
}

namespace trmb
{
	class SoundPlayer;
}

class World
{
public:
										World(sf::RenderTarget &outputTarget, trmb::FontHolder &fonts, trmb::SoundPlayer &sounds);
										World(const World &) = delete;
	World &								operator=(const World &) = delete;

	void								draw();


private:
	void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Middleground,
		Foreground,
		LayerCount
	};


private:
	sf::RenderTarget							&mTarget;
	sf::View									mWorldView;
	trmb::TextureHolder							mTextures;
	trmb::FontHolder							&mFonts;
	trmb::SoundPlayer							&mSounds;
	
	trmb::SceneNode								mSceneGraph;
	std::array<trmb::SceneNode *, LayerCount>	mSceneLayers;

	sf::FloatRect								mWorldBounds;
};

#endif
