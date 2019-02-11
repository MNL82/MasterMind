#include "MasterMind.h"

namespace MM {


MasterMind::MasterMind()
{
}

MasterMind::MasterMind(Configuration config)
	: m_config(config)
{
}


MasterMind::~MasterMind()
{
}

MasterMind::State MasterMind::state() const
{
	return m_state;
}

const Configuration & MasterMind::config() const
{
	return m_config;
}

} // namespace MM
