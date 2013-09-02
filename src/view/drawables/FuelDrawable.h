#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../model/IActorFwd.h"
#include "../../Content.h"

namespace view {

class FuelDrawable : public ::sf::Drawable
{
public:
	FuelDrawable( ::model::IActor* pActor,
		          Content*         pContent );

	~FuelDrawable();

	void draw(::sf::RenderTarget& target, ::sf::RenderStates states) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
