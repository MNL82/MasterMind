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

void ColorCombination::update(int combinationCount)
{
	ASSERT(combinationCount > 0);
	if (static_cast<int>(m_colors.size()) != combinationCount) {
		m_colors.resize(combinationCount);
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

int ColorCombination::color(int index) const
{
	ASSERT(index >= 0 && index < static_cast<int>(m_colors.size()));
	return m_colors[index];
}

void ColorCombination::setColor(int index, int color)
{
	ASSERT(index >= 0 && index < static_cast<int>(m_colors.size()));
	ASSERT(color >= 0);
	m_colors[index] = color;
}

void ColorCombination::resetColors()
{
	for (int &c : m_colors) {
		c = 0;
	}
}

} // namespace MM
