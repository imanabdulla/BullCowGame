/* The game logic(no view code or direct user interaction)
the game is a simple guess the word game is a Mastermind
*/


#pragma once

#include <string>

using FString = std::string; //to make syntax unreal friendly

//initialze bulls and cows values to 0
struct  BullsCowsCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EWordStatus
{
	Invalid,
	Ok,
	Not_isogram,
	Not_WordLength,
	Not_LowerCase,
};

class FBullsCowsGame
{
public:
	FBullsCowsGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	FString GetHiddenWord();
	int32 GetHiddenWordLength()const;
	EWordStatus CheckGuessValidity(FString Guess) const;
	bool IsGameWon() const;

	EWordStatus Reset();
	BullsCowsCount SubmitValidGuess(FString Guess);
	
	~FBullsCowsGame();

private:
	//see the constractor for initialization
	int32 MyCurrentGuess;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString Guess) const; 
	bool IsLowerCase(FString Guess) const;
};

