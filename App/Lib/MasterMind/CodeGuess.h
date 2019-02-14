#pragma once

#include "ColorCombination.h"

namespace MM {

struct Result {
	int rightPosition = -1;
	int rightColor = -1;

	bool isValid() const { 
		return rightPosition != -1 && 
			   rightColor != -1;  
	}
};


class CodeGuess
{
public:
	CodeGuess(const ColorCombination *code);
	~CodeGuess();

	const ColorCombination &colorCombination() const;

	// Color combinations can not be changed after result have been calculated
	bool setColor(int index, int color);
	bool setColors(const ColorCombination &colors);
	bool resetColors();

	const Result &result() const;
	bool isCorrect() const;

	bool calculateResult();

private:
	const ColorCombination *m_code;
	ColorCombination m_colorCombination;

	Result m_result;
};

} // namespace MM
