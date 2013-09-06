#pragma once

#include <memory>

namespace model {

class HighScoreActor
{
public:

	HighScoreActor();

	~HighScoreActor();

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
