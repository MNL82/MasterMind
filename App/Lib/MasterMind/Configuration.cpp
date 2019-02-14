#include "Configuration.h"

#if WIN32
#include <crtdbg.h>
#define ASSERT _ASSERTE
#else
#include <assert.h>
#define ASSERT assert
#endif

namespace MM {

std::vector<std::pair<std::string, std::string>> Configuration::s_colorList = { {"Transparent", "#00000000" }, // 0  - Transparent
														                        {"White", "#ffffff" },     // 1  - White 
																				{"Black", "#000000" },     // 2  - Black 
																				{"Read", "#ff0000" },      // 3  - Read 
																				{"Green", "#00ff00" },     // 4  - Green 
																				{"Blue", "#0000ff" },      // 5  - Blue 
																				{"Yellow", "#ffff00" },    // 6  - Yellow 
																				{"Turquoise", "#00ffff" }, // 7  - Turquoise 
																				{"Purple", "#ff00ff" },    // 8  - Purple 
																				{"Orange", "#ff8800" },    // 9  - Orange 
																				{"Grey", "#888888" } };    // 10 - Grey

Configuration::Configuration()
{
}

Configuration::Configuration(const Configuration & copy)
{
	*this = copy;
}


Configuration::~Configuration()
{
}

void Configuration::operator=(const Configuration & other)
{
	m_colorCount = other.m_colorCount;
	m_triesCount = other.m_triesCount;
	m_columnCount = other.m_columnCount;
}

bool Configuration::operator==(const Configuration & other) const
{
	return m_colorCount == other.m_colorCount &&
		   m_triesCount == other.m_triesCount &&
		   m_columnCount == other.m_columnCount;
}

bool Configuration::operator!=(const Configuration & other) const
{
	return !(*this == other);
}

int Configuration::colorCount() const
{
	return m_colorCount;
}

bool Configuration::setColorCount(int count)
{
	if (count < MM_COLOR_MIN_COUNT || count > MM_COLOR_MAX_COUNT) { return false; }
	if (count != m_colorCount) {
		m_colorCount = count;
	}
	return true;
}

int Configuration::triesCount() const
{
	return m_triesCount;
}

bool Configuration::setTriesCount(int count)
{
	if (count < MM_TRIES_MIN_COUNT) { return false; }
	if (count != m_triesCount) {
		m_triesCount = count;
	}
	return true;
}

int Configuration::columnCount() const
{
	return m_columnCount;
}

bool Configuration::setColumnCount(int count)
{
	if (count < MM_COLUMNS_MIN_COUNT || count > MM_COLUMNS_MAX_COUNT) { return false; }
	if (count != m_columnCount) {
		m_columnCount = count;
	}
	return true;
}

const std::string & Configuration::colorFromInt(int color)
{
	ASSERT(color > 0 || color <= MM_COLOR_MAX_COUNT);
	return s_colorList[color].second;
}

const std::string & Configuration::colorNameFromInt(int color)
{
	ASSERT(color > 0 || color <= MM_COLOR_MAX_COUNT);
	return s_colorList[color].first;
}

int Configuration::colorToInt(const std::string & color)
{
	for (int i = 1; i <= MM_COLOR_MAX_COUNT; i++)
	{
		if (color == s_colorList[i].first || color == s_colorList[i].second) {
			return i;
		}
	}
	ASSERT(false);
	return 0;
}

} // namespace MM
