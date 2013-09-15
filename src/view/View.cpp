#include "View.h"
#include "drawables/FuelDrawable.h"
#include "drawables/PlanetDrawable.h"
#include "drawables/ScoreDrawable.h"
#include "../model/IActor.h"
#include "../model/actors/FuelActor.h"
#include "../model/actors/PlanetActor.h"
#include "../model/actors/ScoreActor.h"
#include "drawables/RocketDrawable.h"
#include "drawables/FuelMeterDrawable.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace view {

class View::Impl
{
public:
	Impl( Content* pContent )
	: m_pContent( pContent )
	, m_apRenderWindow( new sf::RenderWindow( sf::VideoMode( 800, 600 ), "Rocket Rampage" ) )
	, m_gameView()
	, m_guiView()
	, m_gameDrawables()
	, m_guiDrawables()
	{
	}

	void init()
	{

	}

	void update()
	{
		m_apRenderWindow->clear( sf::Color::Black );

		drawGame();

		drawGui();

		m_apRenderWindow->display();
	}

	bool isOpen()
	{
		return m_apRenderWindow->isOpen();
	}

	void notify( const model::Event& e )
	{
		model::EventType type = e.getType();
		switch ( type )
		{
		case model::EV_ADD_FUEL:
			handleAddFuel( e.getValue() );
			break;
		case model::EV_ADD_PLANET:
			handleAddPlanet( e.getValue() );
			break;
		case model::EV_ADD_SCORE:
			handleAddScore( e.getValue() );
			break;
		case model::EV_ADD_ROCKET:
			handleAddRocket( e.getValue() );
			handleAddFuelMeter( e.getValue() );
		default:
			break;
		}
	}

	void handleAddFuel( const boost::any& value )
	{
		try
		{
			model::IActor* pActor = boost::any_cast<model::IActor*>( value );
			m_gameDrawables.insert( DrawableMap::value_type( pActor->getId(), new FuelDrawable( pActor, m_pContent ) ) );
		}
		catch ( const boost::bad_any_cast& )
		{
		}
	}

	void handleAddPlanet( const boost::any& value )
	{
		try
		{
			model::PlanetActor* pActor = boost::any_cast<model::PlanetActor*>( value );
			m_gameDrawables.insert( DrawableMap::value_type( pActor->getId(), new PlanetDrawable( pActor, m_pContent ) ) );
		}
		catch ( const boost::bad_any_cast& )
		{
		}
	}

	void handleAddScore( const boost::any& value )
	{
		try
		{
			model::ScoreActor* pActor = boost::any_cast<model::ScoreActor*>( value );
			m_guiDrawables.insert( DrawableMap::value_type( pActor->getId(), new ScoreDrawable( pActor, m_pContent ) ) );
		}
		catch ( const boost::bad_any_cast& )
		{
		}
	}

	void handleAddRocket( const boost::any& value )
	{
		try
		{
			model::RocketActor* pActor = boost::any_cast<model::RocketActor*>( value );
			m_gameDrawables.insert( DrawableMap::value_type( pActor->getId(), new RocketDrawable( pActor, m_pContent, &m_gameView ) ) );
		}
		catch ( const boost::bad_any_cast& )
		{
		}
	}

	void handleAddFuelMeter( const boost::any& value )
	{
		try
		{
			model::RocketActor* pActor = boost::any_cast<model::RocketActor*>( value );
			m_guiDrawables.insert( DrawableMap::value_type( pActor->getId(), new FuelMeterDrawable( pActor, m_pContent ) ) );
		}
		catch ( const boost::bad_any_cast& )
		{
		}
	}

	bool readEvent( ::sf::Event& event )
	{
		return m_apRenderWindow->pollEvent( event );
	}

private:

	Content* m_pContent;

	::std::auto_ptr< ::sf::RenderWindow > m_apRenderWindow;

	::sf::View m_gameView;

	::sf::View m_guiView;

	typedef ::std::map< ::model::ActorId, ::sf::Drawable* > DrawableMap;

	DrawableMap m_gameDrawables;

	DrawableMap m_guiDrawables;

	void drawGame()
	{
		m_apRenderWindow->setView( m_gameView );

		for( DrawableMap::iterator it( m_gameDrawables.begin() );
			 it != m_gameDrawables.end();
			 ++it )
		{
			m_apRenderWindow->draw( *(it->second) );
		}
	}

	void drawGui()
	{
		m_apRenderWindow->setView( m_guiView );

		for( DrawableMap::iterator it( m_guiDrawables.begin() );
			 it != m_guiDrawables.end();
			 ++it )
		{
			m_apRenderWindow->draw( *(it->second) );
		}
	}

};

View::View( Content* pContent )
: m_apImpl( new Impl( pContent ) )
{
}

View::~View()
{
}

void View::init()
{
	m_apImpl->init();
}

void View::update()
{
	m_apImpl->update();
}

bool View::isOpen()
{
	return m_apImpl->isOpen();
}

void View::notify( const model::Event& e )
{
	m_apImpl->notify( e );
}

bool View::readEvent( ::sf::Event& event )
{
	return m_apImpl->readEvent( event );
}

}
