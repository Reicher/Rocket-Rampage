#include "View.h"
#include "drawables/FuelDrawable.h"
#include "../model/IActor.h"
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
		return true;
	}

	void notify( std::string what, ::model::IActor* pActor )
	{
		if( what == "addFuel" )
		{
			m_drawables.insert( DrawableMap::value_type( pActor->getId(), new FuelDrawable( pActor, m_pContent ) ) );
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

void View::notify( std::string what, ::model::IActor* pActor )
{
	m_apImpl->notify( what, pActor );
}

}
