#pragma once

#include <memory>

namespace controller {

//! Controller for the game
class Controller
{
public:
	Controller();

	~Controller();

	//! Updates the controller
	//!
	//! @param dt seconds elapsed since the last update call.
	void update( float dt );

	//! Returns if the game is on
	bool isGameOn();

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};

} // namespace controller
