#include <fstream>
#include <sstream>
#include "HighScoreFileStorage.h"

HighScoreFileStorage::HighScoreFileStorage()
: m_fileName("HIGHSCORE.TXT")
, m_highScoreCache()
{
}

const HighScoreList& HighScoreFileStorage::getHighScoreList()
{
	if (m_highScoreCache.empty())
	{
		readScoreFromFile();
	}

	return m_highScoreCache;
}

void HighScoreFileStorage::updateHighScoreList(const HighScoreList& newHighScoreList)
{
	m_highScoreCache = newHighScoreList;
	writeScoreToFile();
}

void HighScoreFileStorage::readScoreFromFile()
{
	std::ifstream fileStream(m_fileName.c_str());

	if (fileStream.is_open())
	{
		std::string line;
		HighScoreEntry entry;
		while (std::getline(fileStream, line))
		{
			if (parseHighScoreEntry(line, entry))
			{
				m_highScoreCache.push_back(entry);
			}
		}

		fileStream.close();
	}
}

void HighScoreFileStorage::writeScoreToFile()
{
	std::ofstream fileStream(m_fileName.c_str());

	if (fileStream.is_open())
	{
		for (HighScoreList::iterator it = m_highScoreCache.begin(),
			 endIt = m_highScoreCache.end();
			 it != endIt;
			 ++it)
		{
			fileStream << it->getName() << ":" << it->getScore() << std::endl;
		}

		fileStream.close();
	}
}

bool HighScoreFileStorage::parseHighScoreEntry(const std::string& line, HighScoreEntry& entry)
{
	std::istringstream iss(line);
	std::string name;
	std::string scoreStr;
	if (std::getline(iss, name, ':') && std::getline(iss, scoreStr))
	{
		int score;
		std::stringstream(scoreStr) >> score;

		entry.setName(name);
		entry.setScore(score);

		return true;
	}

	return false;
}






