#include "CLift.h"

using namespace sf;
using namespace sses;
using namespace ssvsc;
using namespace ssvs::Utils;

namespace cb
{
	CLift::CLift(Entity& mEntity, CBGame& mCBGame, ssvsc::Body& mBody, Vector2f mVelocity) : Component(mEntity, "lift"), cbGame(mCBGame), body(mBody), velocity{mVelocity}
	{
		body.onDetection += [&](DetectionInfo mDetectionInfo)
		{
			if(mDetectionInfo.userData == nullptr) return;
			//Entity* entity(static_cast<Entity*>(mDetectionInfo.userData));
			if(Utils::getMin1DIntersection(body.getShape(), mDetectionInfo.body.getShape()).y > 0)
				mDetectionInfo.body.setVelocityY(0);
		};

		body.setVelocity(velocity);
	}

	void CLift::update(float) { }
}
