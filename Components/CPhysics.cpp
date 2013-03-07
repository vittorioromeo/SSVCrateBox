// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CPhysics.h"
#include "Utils.h"

using namespace ssvs::Utils;
using namespace sses;
using namespace std;
using namespace sf;
using namespace ssvsc;
using namespace cb::Utils;

namespace cb
{
	CPhysics::CPhysics(Entity& mEntity, CBGame& mCBGame, World& mWorld, bool mIsStatic, Vector2i mPosition, Vector2i mSize, bool mNoGravity)
		: Component(mEntity, "physics"), cbGame(mCBGame), world(mWorld), body(world.create(mPosition, mSize, mIsStatic)), noGravity{mNoGravity}
	{
		body.onDetection += [&](DetectionInfo mDetectionInfo)
		{
			if(mDetectionInfo.userData == nullptr) return;
			Entity* entity(static_cast<Entity*>(mDetectionInfo.userData));
			onDetection(*entity);
		};
		body.onResolution += [&](ResolutionInfo mResolutionInfo)
		{
			onResolution(mResolutionInfo.resolution);

			lastResolution = mResolutionInfo.resolution;
			if(mResolutionInfo.resolution.x > 0) crushLeft = true;
			else if(mResolutionInfo.resolution.x < 0) crushRight = true;
			if(mResolutionInfo.resolution.y > 0) crushTop = true;
			else if(mResolutionInfo.resolution.y < 0) crushBottom = true;
		};
		body.onPreUpdate += [&]
		{
			lastResolution = {0, 0};
			crushLeft = crushRight = crushTop = crushBottom = false;
		};
		body.onPostUpdate += [&]
		{
			if(!contains(body.getGroups(), "crushable")) return;
			
			if(crushLeft && crushRight) body.setWidth(body.getWidth() - abs(lastResolution.x));
			else if(crushTop && crushBottom) body.setHeight(body.getHeight() - abs(lastResolution.y));

			if(body.getWidth() < 200 || body.getHeight() < 200) getEntity().destroy();
		};
		
		body.setUserData(&getEntity());
	}
	CPhysics::~CPhysics() { body.destroy(); }

	Body& CPhysics::getBody() { return body; }
	bool CPhysics::isNoGravity() { return noGravity; }
}

