#include "Configuration.h"

namespace MM {


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
	m_playerName = other.m_playerName;
}

bool Configuration::operator==(const Configuration & other)
{
	return m_colorCount == other.m_colorCount &&
		   m_triesCount == other.m_triesCount &&
		   m_columnCount == other.m_columnCount &&
	       m_playerName == other.m_playerName;
}

bool Configuration::operator!=(const Configuration & other)
{
	return !(*this == other);
}

int Configuration::colorCount() const
{
	return m_colorCount;
}

bool Configuration::setColorCount(int count)
{
	if (count < 2 || count > 10) { return false; }
	m_colorCount = count;
	return true;
}

int Configuration::triesCount() const
{
	return m_triesCount;
}

bool Configuration::setTriesCount(int count)
{
	if (count < 1) { return false; }
	m_triesCount = count;
	return true;
}

int Configuration::columnCount() const
{
	return m_columnCount;
}

bool Configuration::setColumnCount(int count)
{
	if (count < 2 || count > 10) { return false; }
	m_columnCount = count;
	return true;
}

const std::string & Configuration::playerName() const
{
	return m_playerName;
}

bool Configuration::setPlayerName(const std::string & name)
{
	m_playerName = name;
	return false;
}

} // namespace MM
