#include "Controller.h"
#include "../model/Model.h"
#include "../view/View.h"
#include "../Content.h"

namespace controller {

class Controller::Impl
{
public:
	Impl()
	: m_content()
	, m_model()
	, m_view( &m_content )
	, m_isGameOn( true )
	, m_viewEvent()
	{
		m_view.init();

		m_model.addObserver( &m_view );

		m_model.init();
	}

	void update( float dt )
	{
		if( dt == 0 )
		{
			return;
		}

	    //! Read all events from the view and keyboard
		while ( m_view.readEvent( m_viewEvent ) )
	    {
	    	 switch( m_viewEvent.type )
	    	 {
	    	 case ::sf::Event::Closed:
	    		 shutdown();
	    	 break;

	    	 case ::sf::Event::KeyPressed:
	    		 handleKeyPressed( m_viewEvent.key.code );
	    	 break;

	    	 case ::sf::Event::KeyReleased:
	    		 handleKeyReleased( m_viewEvent.key.code );
	    	 break;

	    	 default:
	    	 break;
	    	 }
	    }

		m_model.update( dt );

		m_view.update();
	}

	bool isGameOn()
	{
		return m_isGameOn;
	}

private:

	Content m_content;

	::model::Model m_model;

	::view::View m_view;

	bool m_isGameOn;

	::sf::Event m_viewEvent;

	void shutdown()
	{

	}

	void handleKeyPressed( ::sf::Keyboard::Key code )
	{
		switch( code )
		{
		case ::sf::Keyboard::W:
			m_model.setRocketThrust( true, 0 );
		break;

		default:
		break;
		}
	}

	void handleKeyReleased( ::sf::Keyboard::Key code )
	{
		switch( code )
		{
			case ::sf::Keyboard::W:
				m_model.setRocketThrust( false, 0 );
			break;

			default:
			break;
		}
	}
};

Controller::Controller()
: m_apImpl( new Impl )
{
}

Controller::~Controller()
{
}

void Controller::update( float dt )
{
	m_apImpl->update( dt );
}

bool Controller::isGameOn()
{
	return m_apImpl->isGameOn();
}

} //namespace controller
