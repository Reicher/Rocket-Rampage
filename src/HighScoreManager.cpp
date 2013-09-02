#include "HighScoreManager.h"
#include "HighScoreFileStorage.h"

HighScoreManager::HighScoreManager()
: m_apStorage()
{
	m_apStorage.reset(new HighScoreFileStorage());
}
