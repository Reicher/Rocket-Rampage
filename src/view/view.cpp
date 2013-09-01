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
