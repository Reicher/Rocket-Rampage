#include <memory>
#include "../model/model.h"

//! View of the game
class View
{
public:
	View();

	~View();

	//! Updates the view
	void update();

	//! Is the view open
	bool isOpen();

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};
