#include "View.h"
#include "drawables/FuelDrawable.h"
#include "drawables/PlanetDrawable.h"
#include "drawables/ScoreDrawable.h"
#include "../model/IActor.h"
#include "../model/actors/ScoreActor.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace view {

class View::Impl
{
public:
	Impl( Content* pContent )
	: m_pContent( pContent )
	, m_apRenderWindow( new sf::RenderWindow( sf::VideoMode( 800, 600 ), "Rocket Rampage" ) )
	, m_apView( new sf::View )
	, m_drawables()
	{
	}

	void init()
	{

	}

	void update()
	{
		m_apRenderWindow->clear( sf::Color::Black );

		draw();

		m_apRenderWindow->setView( *m_apView );

		m_apRenderWindow->display();
	}

	bool isOpen()
	{
		return m_apRenderWindow->isOpen();
	}

	void notify( std::string what, void* p )
	{
		if( what == "addFuel" )
		{
			model::IActor* pActor = static_cast<model::IActor*>( p );
			m_drawables.insert( DrawableMap::value_type( pActor->getId(), new FuelDrawable( pActor, m_pContent ) ) );
		}
		else if( what == "addPlanet" )
		{
			model::PlanetActor* pActor = static_cast<model::PlanetActor*>( p );
			m_drawables.insert( DrawableMap::value_type( pActor->getId(), new PlanetDrawable( pActor, m_pContent ) ) );
		}
		else if( what == "addScore" )
		{
			model::ScoreActor* pActor = static_cast<model::ScoreActor*>( p );
			m_drawables.insert( DrawableMap::value_type( pActor->getId(), new ScoreDrawable( pActor, m_pContent ) ) );
		}
	}

private:

	Content* m_pContent;

	::std::auto_ptr< ::sf::RenderWindow > m_apRenderWindow;

	::std::auto_ptr< ::sf::View > m_apView;

	typedef ::std::map< ::model::ActorId, ::sf::Drawable* > DrawableMap;

	DrawableMap m_drawables;

	void draw()
	{
		for( DrawableMap::iterator it( m_drawables.begin() );
			 it != m_drawables.end();
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

void View::notify( std::string what, void* p )
{
	m_apImpl->notify( what, p );
}

}
