#pragma once

#include <string>

namespace MM {

class Configuration
{
public:
	Configuration();
	Configuration(const Configuration &copy);

	~Configuration();

	void operator=(const Configuration &other);
	bool operator==(const Configuration &other);
	bool operator!=(const Configuration &other);

	int colorCount() const;
	bool setColorCount(int count);

	int triesCount() const;
	bool setTriesCount(int count);

	int columnCount() const;
	bool setColumnCount(int count);

	const std::string &playerName() const;
	bool setPlayerName(const std::string &name);

private:
	// Initialized with default values
	int m_colorCount = 6;
	int m_triesCount = 10;
	int m_columnCount = 4;
	std::string m_playerName = "player";
};

} // namespace MM
