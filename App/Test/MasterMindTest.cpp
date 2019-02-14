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
	REQUIRE(mm.state() == MasterMind::State::Invalid);
}

TEST_CASE("Initial Configuration") {
	Configuration mmc;
	REQUIRE(mmc.colorCount() == MM_COLOR_DEFAULT);
	REQUIRE(mmc.triesCount() == MM_TRIES_DEFAULT);
	REQUIRE(mmc.columnCount() == MM_COLUMNS_DEFAULT);
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
	REQUIRE(guess.result().rightPosition == 1);
	REQUIRE(guess.result().rightColor == 1);
	REQUIRE_FALSE(guess.isCorrect());

	REQUIRE_FALSE(guess.setColor(2, 1));

	CodeGuess guess2(&code);
	guess2.setColor(0, 1);
	guess2.setColor(1, 2);
	guess2.setColor(2, 3);
	guess2.setColor(3, 4);
	REQUIRE(guess2.calculateResult());
	REQUIRE(guess2.result().rightPosition == 4);
	REQUIRE(guess2.result().rightColor == 0);
	REQUIRE(guess2.isCorrect());
}

TEST_CASE("") {
	Configuration c;
	c.setColorCount(8);
	c.setColumnCount(5);
	c.setTriesCount(12);

	MasterMind mm(c);

	REQUIRE(mm.config().columnCount() == 5);
	mm.randomCodeColors();

	//std::cout << "Color Count: " << mm.config().colorCount() << std::endl;
	//for (int n = 0; n < 10; n++) {
	//	mm.randomCodeColors();	
	//	REQUIRE(mm.state() == MasterMind::State::Initial);
	//	for (int i = 0; i < mm.config().columnCount(); i++)
	//	{
	//		std::cout << mm.codeColorCombination().color(i) << " ";
	//	}
	//	std::cout << std::endl;
	//}
	
	REQUIRE(mm.currentGuessIndex() == 0);
	REQUIRE_FALSE(mm.calculateGuessResult());

	for (int i = 0; i < mm.config().columnCount(); i++)
	{
		mm.setGuessColor(i, i + 1);
	}
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.state() == MasterMind::State::InProgress);
	REQUIRE(mm.currentGuessIndex() == 1);
//
	// Reset MasterMind
	c.setColorCount(10);
	c.setColumnCount(4);
	mm.setConfig(c);

	// Set the code
	mm.setCodeColor(0, 4);
	mm.setCodeColor(1, 7);
	mm.setCodeColor(2, 3);
	mm.setCodeColor(3, 8);

	// 1. guess
	mm.setGuessColor(0, 6);
	mm.setGuessColor(1, 6);
	mm.setGuessColor(2, 7);
	mm.setGuessColor(3, 7);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 1);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 0);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 1);
	REQUIRE(mm.state() == MasterMind::State::InProgress);

	// 2. guess
	mm.setGuessColor(0, 8);
	mm.setGuessColor(1, 3);
	mm.setGuessColor(2, 3);
	mm.setGuessColor(3, 6);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 2);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 1);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 1);
	REQUIRE(mm.state() == MasterMind::State::InProgress);

	// 3. guess
	mm.setGuessColor(0, 4);
	mm.setGuessColor(1, 8);
	mm.setGuessColor(2, 4);
	mm.setGuessColor(3, 6);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 3);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 1);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 1);
	REQUIRE(mm.state() == MasterMind::State::InProgress);

	// 4. guess
	mm.setGuessColor(0, 1);
	mm.setGuessColor(1, 1);
	mm.setGuessColor(2, 8);
	mm.setGuessColor(3, 6);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 4);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 0);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 1);
	REQUIRE(mm.state() == MasterMind::State::InProgress);

	// 5. guess
	mm.setGuessColor(0, 7);
	mm.setGuessColor(1, 3);
	mm.setGuessColor(2, 4);
	mm.setGuessColor(3, 8);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 5);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 1);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 3);
	REQUIRE(mm.state() == MasterMind::State::InProgress);

	// 6. guess
	mm.setGuessColor(0, 4);
	mm.setGuessColor(1, 7);
	mm.setGuessColor(2, 3);
	mm.setGuessColor(3, 8);
	REQUIRE(mm.calculateGuessResult());
	REQUIRE(mm.currentGuessIndex() == 5);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightPosition == 1);
	REQUIRE(mm.guess(mm.currentGuessIndex() - 1).result().rightColor == 3);
	REQUIRE(mm.state() == MasterMind::State::Success);
	REQUIRE(mm.currentGuess().isCorrect());
}

//"#ffffff",   // 1  - White 
//"#000000",   // 2  - Black 
//"#ff0000",   // 3  - Red 
//"#00ff00",   // 4  - Green 
//"#0000ff",   // 5  - Blue 
//"#ffff00",   // 6  - Yellow 
//"#00ffff",   // 7  - Turquoise 
//"#ff00ff",   // 8  - Purple 
//"#ff8800",   // 9  - Orange 
//"#888888"};  // 10 - Grey