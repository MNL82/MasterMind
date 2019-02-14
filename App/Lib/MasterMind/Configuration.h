#pragma once

#include <vector>

namespace MM {

#define MM_COLOR_MIN_COUNT 2
#define MM_COLOR_DEFAULT   6
#define MM_COLOR_MAX_COUNT 10

#define MM_COLUMNS_MIN_COUNT 2
#define MM_COLUMNS_DEFAULT   4
#define MM_COLUMNS_MAX_COUNT 10

#define MM_TRIES_MIN_COUNT 4
#define MM_TRIES_DEFAULT   12
#define MM_TRIES_MAX_COUNT 100

class Configuration
{
public:
	Configuration();
	Configuration(const Configuration &copy);

	~Configuration();

	void operator=(const Configuration &other);
	bool operator==(const Configuration &other) const;
	bool operator!=(const Configuration &other) const;

	int colorCount() const;
	bool setColorCount(int count);

	int triesCount() const;
	bool setTriesCount(int count);

	int columnCount() const;
	bool setColumnCount(int count);

	static const std::string &colorFromInt(int color);
	static const std::string &colorNameFromInt(int color);
	static int colorToInt(const std::string &);

private:
	// Initialized with default values
	int m_colorCount = MM_COLOR_DEFAULT;
	int m_triesCount = MM_TRIES_DEFAULT;
	int m_columnCount = MM_COLUMNS_DEFAULT;

	// Index of the hex value if the integer value of the color
	static std::vector<std::pair<std::string, std::string>> s_colorList;
};

} // namespace MM
