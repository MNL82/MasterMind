#pragma once

#include "Configuration.h"
#include "CodeGuess.h"

#include <vector>
#include <memory>

namespace MM {


class MasterMind
{
public:

	enum class State {
		Invalid = -1,
		Initial = 0,
		InProgress = 1,
		Success = 2,
		Failed = 3
	};

	MasterMind();
	MasterMind(Configuration config);
	~MasterMind();

	State state() const;
	bool acceptInput() const;
	bool finished() const;

	const Configuration &config() const;
	void setConfig(const Configuration &config);
	void reset();

	const ColorCombination &code() const;

	// Code Color combinations can not be changed after first guess have been placed
	bool setCodeColor(int index, int color);
	bool randomCodeColors();

	int currentGuessIndex() const;
	const CodeGuess &guess(int index) const;

	const CodeGuess &currentGuess() const;
	bool setGuessColor(int index, int color);
	bool calculateGuessResult();


private:
	void addCodeGuess();

private:
	State m_state = State::Invalid;
	Configuration m_config;

	ColorCombination m_code;
	std::vector<std::unique_ptr<CodeGuess>> m_guesses;
	int m_currentGuessIndex = -1;
};


} // namespace MM