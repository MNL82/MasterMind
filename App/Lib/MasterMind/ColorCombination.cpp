#include "ColorCombination.h"

#if WIN32
#include <crtdbg.h>
#define ASSERT _ASSERTE
#else
#include <assert.h>
#define ASSERT assert
#endif

namespace MM {

ColorCombination::ColorCombination(int combinationCount)
{
	update(combinationCount);
}


ColorCombination::~ColorCombination()
{

}

void ColorCombination::update(int _combinationCount)
{
	ASSERT(_combinationCount > 0);
	if (_combinationCount != combinationCount()) {
		m_colors.resize(_combinationCount);
	}
}

bool ColorCombination::isValid() const
{
	for (int c : m_colors) {
		if (c == 0) { 
			return false; 
		}
	}
	return true;
}

int ColorCombination::combinationCount() const
{
	return static_cast<int>(m_colors.size());
}

int ColorCombination::color(int index) const
{
	ASSERT(index >= 0 && index < combinationCount());
	return m_colors[index];
}

bool ColorCombination::setColor(int index, int color)
{
	ASSERT(index >= 0 && index < combinationCount());
	if (color < 0 && color > MAX_COUNT_COLORS) { return false; }
	m_colors[index] = color;
	return true;
}

void ColorCombination::resetColors()
{
	for (int &c : m_colors) {
		c = 0;
	}
}

} // namespace MM
