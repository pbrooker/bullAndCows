// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Load words from textfile
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    Isograms = GetValidWords(Words, 4, 8);
    
    SetUpGame();
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
    PrintLine(TEXT("Welcome to the Bull Cows Game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Try guessing the %i letter isogram word"), HiddenWord.Len());
    PrintLine(TEXT("from %i possible words"), Isograms.Num());
    PrintLine(TEXT("You have %i guesses."), Lives);
    PrintLine(TEXT("Type in your guess and press enter \nto begin..."));
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debug line
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len() - 1; ++Index) {
        for (int32 Compare = Index + 1; Compare < Word.Len(); ++Compare) {
            if (Word[Index] == Word[Compare]) {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::EvaluateGuess(const FString& Guess) const
{
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
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{    
    if (Guess == HiddenWord)
    {
        WonGame();
        return;
    }

    // Check const evaluations
    EvaluateGuess(Guess);

    FBullCowCount Counts = GetBullCows(Guess);
    
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Counts.Bulls, Counts.Cows);
    PrintLine(TEXT("You have lost one guess."));
    PrintLine(TEXT("You have %i guesses remaining."), --Lives);

    if (Lives <= 0)
    {
        LostGame();
        return;  
    }

    // return
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Wordlist, const int32 MinLength, const int32 MaxLength) const
{
    TArray<FString> ValidWords;

    for (FString Word : Wordlist)
    {
        if (Word.Len() >= MinLength && Word.Len() <= MaxLength && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Counts;
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            ++Counts.Bulls;
            continue;
        }

        for (int32 CowIndex = 0; CowIndex < Guess.Len(); CowIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[CowIndex])
            {
                ++Counts.Cows;
                break;
            }
        }
    }
    return Counts;
}
