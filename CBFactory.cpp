// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CBFactory.h"
#include "Components/CPhysics.h"
#include "Components/CPlayer.h"
#include "Components/CRender.h"

using namespace sf;
using namespace std;
using namespace sses;
using namespace ssvsc;

namespace cb
{
	CBFactory::CBFactory(CBGame& mCBGame, Manager& mManager, World& mWorld) : cbGame(mCBGame), manager(mManager), world(mWorld) { }

	Entity& CBFactory::createWall(Vector2i mPosition)
	{
		auto cPhysics = manager.createComponent<CPhysics>(cbGame, world, true, mPosition, Vector2i{1600, 1600});
		auto cRender = manager.createComponent<CRender>(cbGame, cPhysics->getBody(), "Images/wall.png");

		Body& body(cPhysics->getBody());
		body.addGroups({"solid"});

		return manager.createEntity("wall", {cPhysics, cRender});
	}
	Entity& CBFactory::createBox(Vector2i mPosition)
	{
		auto cPhysics = manager.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600});
		auto cRender = manager.createComponent<CRender>(cbGame, cPhysics->getBody(), "Images/box.png");

		Body& body(cPhysics->getBody());
		body.addGroups({"solid"});
		body.addGroupsToCheck({"solid"});

		return manager.createEntity("box", {cPhysics, cRender});
	}
	Entity& CBFactory::createPlayer(Vector2i mPosition)
	{
		auto cPhysics = manager.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600});
		auto cPlayer = manager.createComponent<CPlayer>(cbGame, *cPhysics);
		auto cRender = manager.createComponent<CRender>(cbGame, cPhysics->getBody(), "Images/player.png");

		Body& body(cPhysics->getBody());
		body.addGroups({"solid"});
		body.addGroupsToCheck({"solid"});

		return manager.createEntity("player", {cPlayer, cPhysics, cRender});
	}
}
