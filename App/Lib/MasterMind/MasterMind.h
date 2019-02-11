#pragma once

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
	~MasterMind();



	State state() const;

private:
	State m_state = State::Initial;
};


} // namespace MM