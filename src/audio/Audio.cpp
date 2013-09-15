#include "Audio.h"

#include <SFML/Audio.hpp>
#include <map>

namespace audio {

class Audio::Impl
{
public:
	Impl( Content* pContent )
	: m_pContent( pContent )
	{

		//for now...
		m_pContent->m_mainTheme.play();
		m_pContent->m_mainTheme.setLoop(true);
		m_pContent->m_mainTheme.setVolume(75);
	}

	void init()
	{

	}

	void update()
	{

	}

	void notify( const model::Event& e )
	{
		model::EventType type = e.getType();
		switch ( type )
		{
		case model::EV_REMOVE_FUEL:
			handleRemoveFuel();
			break;
		default:
			break;
		}
	}

	bool readEvent( ::sf::Event& event )
	{
		return false; //return m_apRenderWindow->pollEvent( event );
	}

	void handleRemoveFuel( )
	{
		//play remvoe fuel sound
	}

private:

	Content* m_pContent;

};

Audio::Audio( Content* pContent )
: m_apImpl( new Impl( pContent ) )
{
}

Audio::~Audio()
{
}

void Audio::init()
{
	m_apImpl->init();
}

void Audio::update()
{
	m_apImpl->update();
}

void Audio::notify( const model::Event& e )
{
	m_apImpl->notify( e );
}

bool Audio::readEvent( ::sf::Event& event )
{
	return m_apImpl->readEvent( event );
}

}
