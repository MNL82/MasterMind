#include "CodeGuess.h"

#include <algorithm>

namespace MM {

CodeGuess::CodeGuess(const ColorCombination *code)
	: m_code(code), m_colorCombination(code->combinationCount())
{
}

CodeGuess::~CodeGuess()
{
}

const ColorCombination & CodeGuess::colorCombination() const
{
	return m_colorCombination;
}

bool CodeGuess::setColor(int index, int color)
{
	if (m_result.isValid()) { return false; }
	return m_colorCombination.setColor(index, color);
}

bool CodeGuess::setColors(const ColorCombination & colors)
{
	if (m_result.isValid()) { return false; }
	m_colorCombination = colors;
	return true;
}

bool CodeGuess::resetColors()
{
	if (m_result.isValid()) { return false; }
	m_colorCombination.resetColors();
	return true;
}

const Result &CodeGuess::result() const
{
	return m_result;
}

bool CodeGuess::isCorrect() const
{
	if (!m_result.isValid()) { return false; }
	if (m_result.rightColor != 0) { return false; }
	return m_result.rightPosition == m_code->combinationCount();
}

bool CodeGuess::calculateResult()
{
	if (!m_code->isValid()) { return false; }
	if (!m_colorCombination.isValid()) { return false; }

	m_result.rightPosition = 0;
	m_result.rightColor = 0;

	int guessWrongColors[MM_COLOR_MAX_COUNT + 1] = { 0 };
	int codeWrongColors[MM_COLOR_MAX_COUNT + 1] = { 0 };

	for (int i = 0; i < m_code->combinationCount(); i++)
	{
		if (m_code->color(i) == m_colorCombination.color(i)) {
			m_result.rightPosition++;
		} else {
			// Cache wron guess and codes colors
			guessWrongColors[m_colorCombination.color(i)]++;
			codeWrongColors[m_code->color(i)]++;
		}
	}

	// Take the sum of the matcing wrong colors
	for (int i = 1; i <= MM_COLOR_MAX_COUNT; i++)
	{
		m_result.rightColor += std::min(guessWrongColors[i], codeWrongColors[i]);
	}

	return true;
}

} // namespace MM