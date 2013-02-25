// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SFML/Window.hpp>
#include <SSVSCollision.h>
#include <SSVEntitySystem.h>
#include "CPlayer.h"
#include "CRender.h"
#include "Utils.h"

using namespace std;
using namespace sf;
using namespace sses;
using namespace ssvsc;
using namespace cb::Utils;

namespace cb
{
	CPlayer::CPlayer(CBGame& mCBGame, CPhysics& mCPhysics)
		: Component("player"), cbGame(mCBGame), cPhysics(mCPhysics), body(cPhysics.getBody())
	{
		cPhysics.onDetection += [&](Entity& mEntity)
		{
			//if(mEntity.getId() == "box") mEntity.destroy();
		};
		cPhysics.onResolution += [&](Vector2i mMinIntersection)
		{
			if(mMinIntersection.y < 0) canJump = true;
		};
	}

	void CPlayer::update(float)
	{
		float speed{230.f}, jumpSpeed{550.f};
		Vector2f oldVelocity{body.getVelocity()}, newVelocity{oldVelocity};

		newVelocity.x = speed * cbGame.getInputX();
		if(canJump && cbGame.getInputJump() == 1) newVelocity.y = -jumpSpeed;
		body.setVelocity(newVelocity);

		auto& cRender = *(getEntity().getComponents<CRender>("render")[0]);
		if(newVelocity.x < 0) cRender.setFlippedX(true);
		else if(newVelocity.x > 0) cRender.setFlippedX(false);

		canJump = false;
	}
}

