#include <memory>
#include "../model/IObserver.h"

//! View of the game
class View : public IObserver
{
public:
	View();

	~View();

	//! Updates the view
	void update();

	//! Is the view open
	bool isOpen();

	void notify( std::string what );

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};
