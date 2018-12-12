// Fill out your copyright notice in the Description page of Project Settings.

#include "Day05.h"
#include "Misc/Char.h"
#include "Internationalization/Regex.h"
#include "Math/IntRect.h"
#include "Kismet/KismetMathLibrary.h"


ADay05::ADay05()
{
	InputFileName = FString("Input/input05.txt");
}

FString ADay05::CalculateResultA()
{
	auto Lines = LoadInputLines();
	if (Lines.Num() == 0) { return "Error"; }

	auto Chars = Lines[0].GetCharArray();
	Chars.Pop();

	return FString::FromInt(ReduceChain(Chars));
}

FString ADay05::CalculateResultB()
{
	auto Lines = LoadInputLines();
	if (Lines.Num() == 0) { return "Error"; }

	auto Chars = Lines[0].GetCharArray();
	Chars.Pop();

	TArray<TCHAR> FilteredChars;
	for (auto Char : Chars)
	{
		// TODO: leave only one set of letters (Capital or Small)
		FilteredChars.AddUnique(Char);
	}

	TArray<int> Results;
	for (auto FilteredChar : FilteredChars)
	{
		auto Removed = RemoveChars(Chars, FilteredChar);
		auto Result = ReduceChain(Removed);
		// UE_LOG(LogTemp, Warning, TEXT("Res: %d"), Result);
		Results.Add(Result);
	}
	
	Results.Sort();
	if (Results.Num() == 0) { return "Error"; }

	return FString::FromInt(Results[0]);
}

TArray<TCHAR> ADay05::RemoveChars(TArray<TCHAR> InChars, TCHAR Char)
{
	TArray<TCHAR> Result;

	for (auto InChar : InChars)
	{
		auto Diff = InChar - Char;
		if (Diff == 0)
		{
			continue;
		}
		if (FGenericPlatformMath::Abs(Diff) == 32)
		{
			continue;
		}
		Result.Add(InChar);
	}

	// UE_LOG(LogTemp, Warning, TEXT("In: %s, Out: %s"), *GlueChars(InChars), *GlueChars(Result));

	return Result;
}

int ADay05::ReduceChain(TArray<TCHAR> InChain)
{
	TArray<TCHAR> Chars;
	Chars.Append(InChain);

	// TODO: use an iterator
	TCHAR LastChar = 0;
	bool Reload = true;
	for (int Position = (Chars.Num() - 1); Position >= 0; Position--)
	{
		if (Reload)
		{
			LastChar = Chars[Position];
			Reload = false;
			continue;
		}

		if (FGenericPlatformMath::Abs(LastChar - Chars[Position]) == 32)
		{
			// UE_LOG(LogTemp, Warning, TEXT("Char %d = %c - %c."), Chars[Position] - LastChar, Chars[Position], LastChar);
			Chars.RemoveAt(Position);
			Chars.RemoveAt(Position);
		}

		if (Position >= Chars.Num())
		{
			Reload = true;
		}
		else
		{
			LastChar = Chars[Position];
		}
	}

	return Chars.Num();
}

FString ADay05::GlueChars(TArray<TCHAR> Chars)
{
	FString Result;
	for (auto Char : Chars)
	{
		Result.AppendChar(Char);
	}
	return Result;
}