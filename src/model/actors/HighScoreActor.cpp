#include "HighScoreActor.h"

namespace model {

class HighScoreActor::Impl
{
public:

	Impl()
	{
	}

};

HighScoreActor::HighScoreActor()
: m_apImpl( new Impl() )
{
}

HighScoreActor::~HighScoreActor()
{
}

}
