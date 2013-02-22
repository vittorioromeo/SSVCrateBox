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
	CPhysics::CPhysics(CBGame& mCBGame, World& mWorld, bool mIsStatic, Vector2i mPosition, Vector2i mSize)
		: Component("physics"), cbGame(mCBGame), world(mWorld), body(world.create(mPosition, mSize, mIsStatic))
	{
		body.onDetection += [&](DetectionInfo mDetectionInfo)
		{
			if(mDetectionInfo.userData == nullptr) return;
			Entity* entity(static_cast<Entity*>(mDetectionInfo.userData));
			onDetection(*entity);
		};
		body.onResolution += [&](ResolutionInfo mResolutionInfo)
		{
			onResolution(mResolutionInfo.minIntersection);
		};
	}
	CPhysics::~CPhysics() { body.destroy(); }

	void CPhysics::init() { body.setUserData(&getEntity()); }

	Body& CPhysics::getBody() { return body; }
}

