#pragma once

#include <vector>

#include "Configuration.h"

namespace MM {

class ColorCombination
{
public:
	ColorCombination(int combinationCount);
	ColorCombination(const ColorCombination &copy);
	~ColorCombination();

	void operator=(const ColorCombination &other);
	bool operator==(const ColorCombination &other) const;
	bool operator!=(const ColorCombination &other) const;

	void update(int combinationCount, int colorCount = -1);

	bool isValid() const;

	int combinationCount() const;

	// Indexed colors are used
	// Color value of 0 is undefined
	int color(int index) const;
	bool setColor(int index, int color);

	void resetColors();

private:
	std::vector<int> m_colors;
};

} //namespace MM
