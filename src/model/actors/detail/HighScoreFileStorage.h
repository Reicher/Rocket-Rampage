#pragma once

#include "IHighScoreStorage.h"

namespace model {

class HighScoreFileStorage : public IHighScoreStorage
{
public:

	HighScoreFileStorage();

	const HighScoreList& getHighScoreList();

	void updateHighScoreList(const HighScoreList& newHighScoreList);

private:

	void readScoreFromFile();

	void writeScoreToFile();

	bool parseHighScoreEntry(const std::string& line, HighScoreEntry& entry);

	std::string m_fileName;

	HighScoreList m_highScoreCache;

};

}
