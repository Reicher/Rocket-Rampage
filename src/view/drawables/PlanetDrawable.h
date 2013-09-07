#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../model/IActorFwd.h"
#include "../../model/actors/PlanetActor.h"

class Content;


namespace view {

class PlanetDrawable : public ::sf::Drawable
{
public:
	PlanetDrawable( ::model::PlanetActor* pActor,
		          Content*         pContent );

	~PlanetDrawable();

	void draw(::sf::RenderTarget& target, ::sf::RenderStates states) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
