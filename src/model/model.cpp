#include "model.h"
#include "IObserver.h"

class Model::Impl
{
public:
	Impl()
	{
	}

	void start()
	{
	}

	void update()
	{
	}

	void addObserver( IObserver* pObserver )
	{
		m_observers.push_back( pObserver );
	}

private:

	typedef std::list<IObserver*> Observers;

	Observers m_observers;

	void notify( std::string what )
	{
		for( Observers::iterator it( m_observers.begin() );
			 it != m_observers.end();
			 ++it )
		{
			( *it )->notify( what );
		}

	}
};

Model::Model()
: m_apImpl( new Impl )
{
}

Model::~Model()
{
}

void Model::start()
{
	m_apImpl->start();
}

void Model::update()
{
	return m_apImpl->update();
}

void Model::addObserver( IObserver* pObserver )
{
	m_apImpl->addObserver( pObserver );
}
