#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "MasterMind.h"
#include "Configuration.h"
#include "CodeGuess.h"

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

TEST_CASE("Color Combinations") {
	ColorCombination cc(4);
	REQUIRE_FALSE(cc.isValid());

	cc.setColor(0, 4);
	cc.setColor(1, 4);
	cc.setColor(2, 4);
	cc.setColor(3, 4);
	REQUIRE(cc.color(2) == 4);
	REQUIRE(cc.isValid());

	cc.update(6);
	REQUIRE_FALSE(cc.isValid());
	REQUIRE(cc.color(5) == 0);

	cc.setColor(4, 2);
	cc.setColor(5, 1);
	REQUIRE(cc.isValid());
}

TEST_CASE("Guess Color Combinations")
{
	ColorCombination code(4);
	CodeGuess guess(&code);
	REQUIRE_FALSE(guess.result().isValid());
	REQUIRE_FALSE(guess.calculateResult());

	code.setColor(0, 1);
	code.setColor(1, 2);
	code.setColor(2, 3);
	code.setColor(3, 4);

	guess.setColor(0, 4);
	guess.setColor(1, 2);
	guess.setColor(2, 2);
	guess.setColor(3, 2);

	REQUIRE(guess.calculateResult());
	REQUIRE(guess.result().rightLocation == 1);
	REQUIRE(guess.result().rightColor == 1);
	REQUIRE_FALSE(guess.isCorrect());

	REQUIRE_FALSE(guess.setColor(2, 1));

	CodeGuess guess2(&code);
	guess2.setColor(0, 1);
	guess2.setColor(1, 2);
	guess2.setColor(2, 3);
	guess2.setColor(3, 4);
	REQUIRE(guess2.calculateResult());
	REQUIRE(guess2.result().rightLocation == 4);
	REQUIRE(guess2.result().rightColor == 0);
	REQUIRE(guess2.isCorrect());
}
