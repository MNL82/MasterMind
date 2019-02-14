#pragma once

namespace MM {

#define MAX_COUNT_COLORS 10
#define MAX_COUNT_COLUMNS 10

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

private:
	// Initialized with default values
	int m_colorCount = 6;
	int m_triesCount = 10;
	int m_columnCount = 4;
};

} // namespace MM
