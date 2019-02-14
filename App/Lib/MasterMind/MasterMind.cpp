#include "MasterMind.h"

#include <cstdlib>
#include <time.h>
#include <memory>

#if WIN32
#include <crtdbg.h>
#define ASSERT _ASSERTE
#else
#include <assert.h>
#define ASSERT assert
#endif

namespace MM {

MasterMind::MasterMind()
	: m_code(m_config.columnCount())
{
	// Seed for the rand() function
	srand(static_cast<unsigned int>(time(NULL)));
	reset();
}

MasterMind::MasterMind(Configuration config)
	: m_config(config), m_code(config.columnCount())
{
	// Seed for the rand() function
	srand(static_cast<unsigned int>(time(NULL)));
	reset();
}

MasterMind::~MasterMind()
{
}

MasterMind::State MasterMind::state() const
{
	return m_state;
}

bool MasterMind::acceptInput() const
{
	return m_state == State::Initial || m_state == State::InProgress;
}

bool MasterMind::finished() const
{
	return m_state == State::Failed || m_state == State::Success;
}

const Configuration & MasterMind::config() const
{
	return m_config;
}

void MasterMind::setConfig(const Configuration &config)
{
	if (config != m_config) {
		m_config = config;
		m_code.update(m_config.columnCount(), m_config.colorCount());
		// Reset MasterMind
		reset();
	}
}

void MasterMind::reset()
{
	m_guesses.clear();
	m_currentGuessIndex = -1;
	m_state = State::Invalid;

	if (m_code.isValid()) {
		addCodeGuess();
		m_state = State::Initial;
	}
}

const ColorCombination & MasterMind::code() const
{
	return m_code;
}

bool MasterMind::setCodeColor(int index, int color)
{
	if (m_state >= State::InProgress) { return false; }
	if (m_code.setColor(index, color)) {
		reset();
		return true;
	}
	return false;
}

bool MasterMind::randomCodeColors()
{
	if (m_state >= State::InProgress) { return false; }
	for (int i = 0; i < m_config.columnCount(); i++)
	{
		m_code.setColor(i, (std::rand() % m_config.colorCount())+1);
	}
	reset();
	return true;
}

int MasterMind::currentGuessIndex() const
{
	return m_currentGuessIndex;
}

const CodeGuess & MasterMind::guess(int index) const
{
	ASSERT(index >= 0 && index <= m_currentGuessIndex);
	return *m_guesses[index].get();
}

const CodeGuess & MasterMind::currentGuess() const
{
	ASSERT(m_currentGuessIndex > -1);
	return *m_guesses[m_currentGuessIndex].get();
}

bool MasterMind::setGuessColor(int index, int color)
{
	if (!acceptInput()) { return false; }
	return m_guesses[m_currentGuessIndex]->setColor(index, color);
}

bool MasterMind::calculateGuessResult()
{
	ASSERT(m_currentGuessIndex >= 0);
	if (m_guesses[m_currentGuessIndex]->calculateResult()) {

		if (currentGuess().isCorrect()) {
			m_state = State::Success;
		} else if (m_currentGuessIndex + 1 == m_config.triesCount()) {
			m_state = State::Failed;
		} else {
			addCodeGuess();
			m_state = State::InProgress;
		}
		return true;
	}
	return false;
}

void MasterMind::addCodeGuess()
{
	m_guesses.push_back(std::make_unique<CodeGuess>(&m_code));
	m_currentGuessIndex++;
}

} // namespace MM
