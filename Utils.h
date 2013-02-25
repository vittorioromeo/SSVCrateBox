// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CB_UTILS_H
#define CB_UTILS_H

#include <SFML/Graphics.hpp>
#include <SSVStart.h>

namespace cb
{
	namespace Utils
	{
		float toPixels(int mCoords);
		sf::Vector2f toPixels(sf::Vector2i mCoords);
		int toCoords(float mPixels);

		void shakeCamera(ssvs::TimelineManager& mTimelineManager, ssvs::Camera& mCamera);
	}
}

#endif // CB_UTILS_H
