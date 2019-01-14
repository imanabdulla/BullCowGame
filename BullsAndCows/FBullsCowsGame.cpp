#include "pch.h"
#include "FBullsCowsGame.h"
#include <map>

// to make syntax unreal friendly
#define Tmap std::map //data type std::map which is included in <map> library is defined as TMap
using int32 = int;

FBullsCowsGame::FBullsCowsGame() {Reset(); } //default constractor

int32 FBullsCowsGame::GetMaxTries() const 
{
	Tmap <int32, int32> WordLengthToMaxGuesses{ {3, 4}, {4, 7}, {5, 10}, {6, 16} };

	return WordLengthToMaxGuesses[MyHiddenWord.length()]; 
}

int32 FBullsCowsGame::GetCurrentTry() const {return MyCurrentGuess; }

FString FBullsCowsGame::GetHiddenWord()
{
	Tmap <int32, FString> HiddenWordToLength  { {3, "pla"}, { 4, "plan" }, { 5, "plane" }, { 6, "planet" }};
	//TODO ask user to choose the length of hidden word
	//if he choose 3, 4, 5
		//the hidden word would be some specifc word

	return HiddenWordToLength[GetHiddenWordLength()];
}

int32 FBullsCowsGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }

EWordStatus FBullsCowsGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess is not isogram
	{
		return EWordStatus::Not_isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess has uppercas letters
	{
		return EWordStatus::Not_LowerCase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EWordStatus::Not_WordLength;
	}
	else
	{
		return EWordStatus::Ok;
	}
}

bool FBullsCowsGame::IsGameWon() const { return bIsGameWon; }

EWordStatus FBullsCowsGame::Reset()
{
	MyCurrentGuess = 1;

	const FString HIDDEN_WORD = "planet"; //this Must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	return EWordStatus::Ok;
}

BullsCowsCount FBullsCowsGame::SubmitValidGuess(FString Guess)
{
	BullsCowsCount BullsCowsCount;

	int32 WordLength = MyHiddenWord.length(); // assuming hidden word = guess word
	//loop through the HiddenWord
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
		//compare user Guess with the HiddenWord
		for (int32 GWChar = 0; GWChar < WordLength; GWChar++)
		{
			// if they match then
			if (Guess[GWChar] == MyHiddenWord[HWChar]) 
			{
				//if they in the same place
				if (HWChar == GWChar) 
				{
					BullsCowsCount.Bull++; //increment bulls
				}
				else
				{
					BullsCowsCount.Cow++; //increment cows
				}
			}
		}
	}
	
	// increase current guess try
	MyCurrentGuess++;
	
	//check won case
	bIsGameWon = (BullsCowsCount.Bull == WordLength) ?  true : false;
	
	return BullsCowsCount;
}

bool FBullsCowsGame::IsIsogram(FString Guess) const
{	
	//treat 0 and 1 letter Guess is an isogram
	if (Guess.length() <= 1) return true;

	//define map hold guess charachters
	Tmap<char, bool> SeenLetter;
	
	//loop through Guess to fill its characters inside map
	for (auto Letter : Guess)
	{
		//set each character inside Guess as a small letter
		Letter = tolower(Letter);
		
		//check if map is  added this charcter before
		if (SeenLetter[Letter])
			return false;
		else
			SeenLetter[Letter] = true; //insert it inside map
	}
	return true; //for case user type /0 (escape character)
}

bool FBullsCowsGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))  return false;
	}
	return true;
}

FBullsCowsGame::~FBullsCowsGame() {} //default destractor 



