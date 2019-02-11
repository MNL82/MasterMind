#pragma once

#include "Configuration.h"

namespace MM {


class MasterMind
{
public:

	enum class State {
		Initial = 0,
		InProgress = 1,
		Finished = 2
	};

	MasterMind();
	MasterMind(Configuration config);
	~MasterMind();


	State state() const;
	const Configuration &config() const;

private:
	State m_state = State::Initial;
	Configuration m_config;
};


} // namespace MM