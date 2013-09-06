#pragma once

#include <string>
#include <list>

namespace model {

//! @brief A high score storage entry.
class HighScoreEntry
{
public:

	HighScoreEntry()
	: m_name("")
	, m_score(0)
	{
	}

	HighScoreEntry(const std::string& name, int score)
	: m_name(name)
	, m_score(score)
	{
	}

	std::string getName() const
	{
		return m_name;
	}

	void setName(std::string name)
	{
		m_name = name;
	}

	int getScore() const
	{
		return m_score;
	}

	void setScore(int score)
	{
		m_score = score;
	}

private:

	std::string m_name;

	int m_score;

};

typedef std::list<HighScoreEntry> HighScoreList;

//! @brief Interface for a high score storage.
class IHighScoreStorage
{
public:

	virtual ~IHighScoreStorage() {}

	virtual const HighScoreList& getHighScoreList() = 0;

	virtual void updateHighScoreList(const HighScoreList& newHighScoreList) = 0;

};

}
