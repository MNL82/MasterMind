#pragma once

#include <vector>

#include "Configuration.h"

namespace MM {

class ColorCombination
{
public:
	ColorCombination(int combinationCount);
	~ColorCombination();

	void update(int combinationCount);

	bool isValid() const;

	// Indexed colors are used
	// Color value of 0 is undefined
	int color(int index) const;
	void setColor(int index, int color);

	void resetColors();

private:
	std::vector<int> m_colors;
};

} //namespace MM
