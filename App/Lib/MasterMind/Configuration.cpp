#include "Configuration.h"

#if WIN32
#include <crtdbg.h>
#define ASSERT _ASSERTE
#else
#include <assert.h>
#define ASSERT assert
#endif

namespace MM {

std::vector<std::string> Configuration::s_colorList = { "#00000000", // 0  - Transparent
														"#ffffff",   // 1  - White 
                                                        "#000000",   // 2  - Black 
														"#ff0000",   // 3  - Read 
														"#00ff00",   // 4  - Green 
														"#0000ff",   // 5  - Blue 
														"#ffff00",   // 6  - Yellow 
														"#00ffff",   // 7  - Turquoise 
														"#ff00ff",   // 8  - Purple 
														"#ff8800",   // 9  - Orange 
														"#888888"};  // 10 - Grey

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
	if (count < 2 || count > MAX_COUNT_COLORS) { return false; }
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
	if (count < 1) { return false; }
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
	if (count < 2 || count > MAX_COUNT_COLUMNS) { return false; }
	if (count != m_columnCount) {
		m_columnCount = count;
	}
	return true;
}

const std::string & Configuration::colorFromInt(int color)
{
	ASSERT(color > 0 || color <= MAX_COUNT_COLORS);
	return s_colorList[color];
}

int Configuration::colorToInt(const std::string & color)
{
	for (int i = 1; i <= MAX_COUNT_COLORS; i++)
	{
		if (color == s_colorList[i]) {
			return i;
		}
	}
	ASSERT(false);
	return 0;
}

} // namespace MM
