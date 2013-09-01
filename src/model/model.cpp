#include "model.h"

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
