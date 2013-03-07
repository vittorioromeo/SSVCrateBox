// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CBFactory.h"
#include "Components/CPhysics.h"
#include "Components/CPlayer.h"
#include "Components/CRender.h"
#include "Components/CLift.h"

using namespace sf;
using namespace std;
using namespace sses;
using namespace ssvsc;

namespace cb
{
	CBFactory::CBFactory(CBGame& mCBGame, Manager& mManager, World& mWorld) : cbGame(mCBGame), manager(mManager), world(mWorld) { }

	Entity& CBFactory::createWall(Vector2i mPosition)
	{
		auto& result = manager.createEntity("wall");
		auto& cPhysics = result.createComponent<CPhysics>(cbGame, world, true, mPosition, Vector2i{1600, 1600});
		result.createComponent<CRender>(cbGame, cPhysics.getBody(), "Images/wall.png");

		Body& body(cPhysics.getBody());
		body.addGroups({"solid"});

		return result;
	}
	Entity& CBFactory::createBox(Vector2i mPosition)
	{
		auto& result = manager.createEntity("box");
		auto& cPhysics = result.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600});
		result.createComponent<CRender>(cbGame, cPhysics.getBody(), "Images/box.png");

		Body& body(cPhysics.getBody());
		body.addGroups({"solid"});
		body.addGroups({"liftable"});
		body.addGroups({"crushable"});
		body.addGroupsToCheck({"solid"});

		return result;
	}
	Entity& CBFactory::createPlayer(Vector2i mPosition)
	{
		auto& result = manager.createEntity("player");
		auto& cPhysics = result.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600});
		result.createComponent<CPlayer>(cbGame, cPhysics);
		result.createComponent<CRender>(cbGame, cPhysics.getBody(), "Images/player.png");

		Body& body(cPhysics.getBody());
		body.addGroups({"solid"});
		body.addGroups({"liftable"});
		body.addGroups({"crushable"});
		body.addGroupsToCheck({"solid"});

		return result;
	}
	Entity& CBFactory::createLift(Vector2i mPosition, Vector2f mVelocity)
	{
		auto& result = manager.createEntity("lift");
		auto& cPhysics = result.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600}, true);
		result.createComponent<CLift>(cbGame, cPhysics.getBody(), mVelocity);
		auto& cRender =result.createComponent<CRender>(cbGame, cPhysics.getBody(), "Images/lift.png");

		Body& body(cPhysics.getBody());
		body.addGroups({"solid"});
		body.addGroupsToCheck({"solid"});
		body.addGroupsNoResolve({"liftable"});

		if(mVelocity.x == 0) mVelocity.y > 0 ? cRender.setRotation(180) : cRender.setRotation(0);
		else if(mVelocity.y == 0) mVelocity.x > 0 ? cRender.setRotation(90) : cRender.setRotation(270);
		
		return result;
	}
	Entity& CBFactory::createMetalBox(Vector2i mPosition)
	{
		auto& result = manager.createEntity("metalbox");
		auto& cPhysics = result.createComponent<CPhysics>(cbGame, world, false, mPosition, Vector2i{1600, 1600});
		result.createComponent<CRender>(cbGame, cPhysics.getBody(), "Images/metalbox.png");

		Body& body(cPhysics.getBody());
		body.addGroups({"solid"});
		body.addGroups({"liftable"});
		body.addGroupsToCheck({"solid"});

		return result;
	}
}
