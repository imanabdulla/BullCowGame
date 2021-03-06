/*
this is a console execution responsible for any user interaction in game
it acts like a view to MVC pattern
it implement FBullsCowsGame class
*/


#pragma once

#include "pch.h" //created library
#include <iostream> //standard library
#include <string> //standard library
#include "FBullsCowsGame.h"

//to make syntax unreal friendly
using FText = std::string; //namespace
using int32 = int;

//Functions Prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummery();

//Global Variables
FBullsCowsGame BCGame; //instantiate a new game, which we reuse across plays

//Entry Point of Application
int32 main()
{
	bool bPlayAgian = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgian = AskToPlayAgain();
	} 
	while (bPlayAgian);

	return 0; // exit the application
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls And Cows, a fun word game \n";
	//TODO ask user to choose the length of hidden word
	std::cout << "Choose the number of letters for the correct guess (3 ,4 ,5 , 6): ";
	//std::getline()
		//if he choose 3, 4, 5
			//the hidden word would be some specifc word
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letters isogram I'm thinking of? \n \n";
	return;
}

//plays a single game for completion
void PlayGame()
{
	int32 MaxGuesses = BCGame.GetMaxTries();
	//loop for possible guesses valid in game
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxGuesses)
	{
		FText Guess = GetValidGuess();

		//submit valid guess and get couts of bulls and cows
		BullsCowsCount BCCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BCCount.Bull;
		std::cout << ". Cows  = " << BCCount.Cow << std::endl << std::endl;
	}
	
	PrintGameSummery();
}

//
FText GetValidGuess()
{
	EWordStatus Status = EWordStatus::Invalid;
	FText Guess = "";
	do
	{
		//Ask user for the Guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try No." << CurrentTry << " of " << BCGame.GetMaxTries() << " Tries\n";
		std::cout << "Enter Your Guess: ";
		std::getline(std::cin, Guess);

		//check if guess is valid or not
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Not_isogram:
			std::cout << "Please Enter a word without repeating letters. \n\n";
			break;
		case EWordStatus::Not_LowerCase:
			std::cout << "Please Enter all lower case letters. \n\n";
			break;
		case EWordStatus::Not_WordLength:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << "-letter Word. \n\n";
			break;
		default:
			break;
		}
	} while (Status != EWordStatus::Ok);
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you Want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << "===========================================================================" <<std::endl;
	
	//reset the game
	BCGame.Reset();
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WON! \n\n";
	}
	else
	{
		std::cout << "TRY AGAIN! \n\n";
	}
	return;
}
