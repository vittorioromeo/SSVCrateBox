// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Utils.h"

using namespace sf;
using namespace ssvs;
using namespace ssvs::Utils;

namespace cb
{
	namespace Utils
	{
		float toPixels(int mCoords) { return mCoords / 100.f; }
		int toCoords(float mPixels) { return mPixels * 100.f; }
		Vector2f toPixels(Vector2i mCoords) { return Vector2f(mCoords) / 100.f; }

		void shakeCamera(TimelineManager& mTimelineManager, Camera& mCamera)
		{
			int s{8};
			Vector2f oldCenter{mCamera.getCenter()};
			Timeline& timeline(mTimelineManager.create());

			for(int i{s}; i > 1; --i)
			{
				timeline.append<Do>([&mCamera, oldCenter, i]{ mCamera.centerOn(oldCenter + Vector2f{getRnd(-i, i), getRnd(-i, i)}); });
				timeline.append<Wait>(2);
				timeline.append<Go>(0, 5);
			}

			timeline.append<Do>([&mCamera, oldCenter]{ mCamera.centerOn(oldCenter); });
		}
	}
}

