#include "view.h"

class View::Impl
{
public:
	Impl()
	{
	}

	void update()
	{
	}

	bool isOpen()
	{
		return true;
	}

	void notify( std::string what )
	{

	}

};

View::View()
: m_apImpl( new Impl )
{
}

View::~View()
{
}

void View::update()
{
	m_apImpl->update();
}

bool View::isOpen()
{
	return m_apImpl->isOpen();
}

void View::notify( std::string what )
{
	m_apImpl->notify( what );
}
