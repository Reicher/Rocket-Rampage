#pragma once

#include <memory>
#include "IHighScoreStorage.h"

class HighScoreManager
{
public:

	HighScoreManager();

private:

	std::auto_ptr<IHighScoreStorage> m_apStorage;

};
