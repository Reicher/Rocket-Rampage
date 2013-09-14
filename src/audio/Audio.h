#pragma once

#include <memory>
#include "../model/IObserver.h"
#include "../Content.h"

namespace audio {

//! Audio of the game
class Audio : public ::model::IObserver
{
public:
	Audio( Content* pContent );

	~Audio();

	//! Initiates the Audio.
	void init();

	//! Updates the Audio (needed?)
	void update();

	void notify( const model::Event& e );

	bool readEvent( ::sf::Event& event );

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};

}
