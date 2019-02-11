#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "MasterMind.h"

using namespace MM;

TEST_CASE("Instantiate MasterMind")
{
	MasterMind * mm = new MasterMind();
	
	REQUIRE(mm != nullptr);

	delete mm;
	mm = nullptr;
}

TEST_CASE("Initial State") {
	MasterMind mm;
	REQUIRE(mm.state() == MasterMind::State::Initial);
}
