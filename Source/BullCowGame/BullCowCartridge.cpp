// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull|Cows Game! Have fun!"));
    PrintLine(TEXT("Try guessing the isogram word!"));
    PrintLine(TEXT("Press enter to begin"));

    SetUpGame();

    // prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // check player guess

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Your word length is incorrect. Try again!"));
        }
        else {
            PrintLine(TEXT("That is incorrect!"));
        }
    }
   
    // check if isogram
    // check character count
    // check character position
    // remove life
    // check if lives > 0
    // if yes - continue game - show lives left
    // if no - fail and show word - offer to play again
}
    
void UBullCowCartridge::SetUpGame()
{
    HiddenWord = TEXT("word");
    Lives = 4;
}
