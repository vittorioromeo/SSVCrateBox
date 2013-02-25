// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CRender.h"
#include "Utils.h"

using namespace std;
using namespace sf;
using namespace ssvsc;
using namespace cb::Utils;

namespace cb
{
	CRender::CRender(CBGame& mCBGame, Body& mBody, string mTextureId)
		: Component("render"), cbGame(mCBGame), body(mBody), sprite{cbGame.getData().getTexture(mTextureId)}
	{
		auto& rect(sprite.getTextureRect());
		sprite.setOrigin({rect.width / 2.f, rect.height / 2.f});
	}

	void CRender::update(float)
	{
		Vector2f position{toPixels(body.getPosition())}, size{toPixels(body.getSize())};
		sprite.setPosition(position);
		sprite.setScale(size.x / 16.f, size.y / 16.f);
		if(flippedX) sprite.scale(-1, 1);
		if(flippedY) sprite.scale(1, -1);
	}
	void CRender::draw() { cbGame.render(sprite); }

	void CRender::setRotation(float mDegrees)	{ sprite.setRotation(mDegrees); }
	void CRender::setFlippedX(bool mFlippedX)	{ flippedX = mFlippedX; }
	void CRender::setFlippedY(bool mFlippedY)	{ flippedY = mFlippedY; }
	bool CRender::isFlippedX() const          	{ return flippedX; }
	bool CRender::isFlippedY() const         	{ return flippedY; }
	Sprite& CRender::getSprite() 				{ return sprite; }
}

