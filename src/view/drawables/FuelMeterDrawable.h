#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Content;

namespace model {
class RocketActor;
}

namespace view {

class FuelMeterDrawable : public sf::Drawable
{
public:

	FuelMeterDrawable( ::model::RocketActor* pRocketActor, Content* pContent );

	~FuelMeterDrawable();

	void draw( ::sf::RenderTarget& target, ::sf::RenderStates states ) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
