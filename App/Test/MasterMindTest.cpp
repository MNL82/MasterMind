#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "MasterMind.h"
#include "Configuration.h"

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

TEST_CASE("Initial Configuration") {
	Configuration mmc;
	REQUIRE(mmc.colorCount() == 6);
	REQUIRE(mmc.triesCount() == 10);
	REQUIRE(mmc.columnCount() == 4);
}

TEST_CASE("Copy/Compare Configuration") {
	Configuration c1, c2;
	REQUIRE((c1 == c2));
	REQUIRE_FALSE((c1 != c2));

	c2.setColorCount(8);
	c1.setTriesCount(100);
	REQUIRE((c1 != c2));
	REQUIRE_FALSE((c1 == c2));

	Configuration c3 = c1;
	REQUIRE(c3.triesCount() == 100);
	REQUIRE((c1 == c3));
}

TEST_CASE("MasterMind configuration initialization") {
	Configuration c;
	c.setColorCount(10);
	c.setColumnCount(6);
	MasterMind mm(c);
	REQUIRE(mm.config().colorCount() == 10);
	REQUIRE(mm.config().columnCount() == 6);
}