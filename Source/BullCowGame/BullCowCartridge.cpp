// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetUpGame();
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }

    // check player guess
    ProcessGuess(Input);
}
    
void UBullCowCartridge::SetUpGame()
{
    PrintLine(TEXT("Welcome to the Bull|Cows Game! Have fun!"));

    HiddenWord = TEXT("word");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Try guessing the %i letter isogram word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i guesses."), Lives);
    PrintLine(TEXT("Type in your guess and press enter \nto begin..."));
}

void UBullCowCartridge::WonGame()
{
    bGameOver = true;
    ClearScreen();
    PrintLine(TEXT("You win!"));
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::LostGame()
{
    bGameOver = true;
    ClearScreen();
    PrintLine(TEXT("You have no guesses left."));
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
    PrintLine(TEXT("Press enter to try again"));
}

bool UBullCowCartridge::IsIsogram(FString Word)
{
    for (int y = 0; y < Word.Len() - 1; ++y) {
        for (int i = y + 1; i < Word.Len(); ++i) {
            if (Word[y] == Word[i]) {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{    
    if (Guess == HiddenWord)
    {
        WonGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(
            TEXT("Your word length is incorrect.\nThe isogram is %i letters. Try again!"), 
            HiddenWord.Len()
        );
        return;
    }

    // check if isogram
    if (!IsIsogram(Guess))
    {
        // isogram check
        PrintLine(TEXT("No repeating letters, try again"));
    }

    // check character position - return bulls & cows

    PrintLine(TEXT("You have lost one guess."));
    PrintLine(TEXT("You have %i guesses remaining."), --Lives);

    if (Lives <= 0)
    {
        LostGame();
        return;  
    }

    
    // return
}
