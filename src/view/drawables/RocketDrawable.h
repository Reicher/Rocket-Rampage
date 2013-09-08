#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../model/IActorFwd.h"
#include "../../Content.h"
#include "../../model/actors/RocketActor.h"

namespace view {

class RocketDrawable : public ::sf::Drawable
{
public:
	RocketDrawable( ::model::RocketActor* pActor,
		          Content*         pContent,
		          ::sf::View* 		pView);

	~RocketDrawable();

	void draw(::sf::RenderTarget& target, ::sf::RenderStates states) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
