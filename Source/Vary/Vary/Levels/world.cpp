#include "world.h"
#include "../Resources/resourceIdentifiers.h"

#include "Trambo/SceneNodes/spriteNode.h"
#include "Trambo/Sounds/soundPlayer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <algorithm>


World::World(sf::RenderTarget& outputTarget, trmb::FontHolder& fonts, trmb::SoundPlayer& sounds)
: mTarget(outputTarget)
, mTextures()
, mFonts(fonts)
, mSounds(sounds)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, 1600.0, 1200.0)
, mSpawnPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f)
, mCamera(outputTarget.getDefaultView(), mWorldBounds)
, mHero(nullptr)
{
	loadTextures();
	buildScene();

	// ALW - Center the camera on the hero
	mCamera.getView().setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	mSceneGraph.update(dt);					// ALW - Update the hero along with the rest of the scene graph
	mCamera.update();						// ALW - Update the camera position
}

void World::draw()
{
	mTarget.setView(mCamera.getView());
	mTarget.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::ID::Grass,      "Data/Textures/Grass.png");
	mTextures.load(Textures::ID::Heroes,	 "Data/Textures/Heroes.png");
}

void World::buildScene()
{
	// Initialize the different layers

	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		trmb::SceneNode::Ptr layer(new trmb::SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture &GrassTexture = mTextures.get(Textures::ID::Grass);
	GrassTexture.setRepeated(true);

	sf::IntRect textureRect(mWorldBounds);

	// Add the background sprite to the scene
	std::unique_ptr<trmb::SpriteNode> GrassSprite(new trmb::SpriteNode(GrassTexture, textureRect));
	GrassSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(GrassSprite));

	// Add player's character
	std::unique_ptr<Hero> player(new Hero(Hero::Type::Wizard, mTextures, mFonts, mWorldBounds));
	mHero = player.get();
	mHero->setPosition(mSpawnPosition);
	mSceneLayers[Middleground]->attachChild(std::move(player));
	mCamera.setHero(mHero);
}
