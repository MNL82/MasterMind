#pragma once

#include <vector>

#include "Configuration.h"

namespace MM {

class ColorCombination
{
public:
	ColorCombination(int combinationCount);
	~ColorCombination();

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
