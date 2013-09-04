#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../model/IActorFwd.h"
#include "../../Content.h"

namespace view {

class PlanetDrawable : public ::sf::Drawable
{
public:
	PlanetDrawable( ::model::IActor* pActor,
		          Content*         pContent );

	~PlanetDrawable();

	void draw(::sf::RenderTarget& target, ::sf::RenderStates states) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
