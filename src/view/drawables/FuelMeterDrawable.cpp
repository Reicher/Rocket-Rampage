#include "FuelMeterDrawable.h"
#include "../../Content.h"
#include "../../model/actors/RocketActor.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

#include <sstream>

namespace view {

const double WIDTH = 300;
const double HEIGHT = 50;
const double MAX_FUEL = 10;

class FuelMeterDrawable::Impl
{
public:

	Impl( ::model::RocketActor* pRocketActor, Content* pContent )
	: m_pRocketActor( pRocketActor )
	, m_apFuelText( new sf::Text( "Fuel: 0", pContent->m_standardFont, 30 ) )
	, m_apFrameRectangle( new sf::RectangleShape( sf::Vector2f( WIDTH, HEIGHT )) )
	, m_apFuelRectangle( new sf::RectangleShape( sf::Vector2f( WIDTH, HEIGHT )) )
	{
		m_apFrameRectangle->setOutlineThickness(2);
		m_apFrameRectangle->setOutlineColor(sf::Color::White);
		m_apFrameRectangle->setPosition(500, 0);

		m_apFuelRectangle->setFillColor(sf::Color(0, 255, 0));
		m_apFuelRectangle->setPosition(500, 0);

		m_apFuelText->setColor(sf::Color::White);
		m_apFuelText->setPosition( 400.0, 0.0 );
		m_apFuelText->setString("Fuel: ");
	}

	void draw( sf::RenderTarget& target, sf::RenderStates states ) const
	{
		target.draw(*m_apFuelText, states);
		target.draw(*m_apFrameRectangle, states);

		double ratio = m_pRocketActor->getFuel() / MAX_FUEL;

		m_apFuelRectangle->setFillColor( ::sf::Color( (1.0-ratio) * 255.0
									, ratio * 255.0
									, 0.0 ) );

		m_apFuelRectangle->setSize( ::sf::Vector2f( WIDTH * ratio
									, HEIGHT) );

		target.draw(*m_apFuelRectangle, states);
	}

private:
	::model::RocketActor* m_pRocketActor;

	::std::auto_ptr<sf::Text> m_apFuelText;
	::std::auto_ptr<sf::RectangleShape> m_apFrameRectangle;
	::std::auto_ptr<sf::RectangleShape> m_apFuelRectangle;
};

FuelMeterDrawable::FuelMeterDrawable( ::model::RocketActor* pRocketActor, Content* pContent )
: m_apImpl( new Impl( pRocketActor, pContent ) )
{
}

FuelMeterDrawable::~FuelMeterDrawable()
{
}

void FuelMeterDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_apImpl->draw( target, states );
}

}
