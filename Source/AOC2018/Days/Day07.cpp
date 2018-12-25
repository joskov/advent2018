// Fill out your copyright notice in the Description page of Project Settings.

#include "Day07.h"
#include "Internationalization/Regex.h"

ADay07::ADay07()
{
	InputFileName = FString("Input/input07.txt");
}

FString ADay07::CalculateResultA()
{
	auto Lines = LoadInputLines();
	if (Lines.Num() == 0) { return "Error"; }

	TMap<FString, TSet<FString>> WaitMap;
	TArray<FString> AllTasks;

	for (auto Line : Lines)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Line: %s"), *Line);
		FString Left;
		FString Right;
		auto Parsed = ParseLine(Line, OUT Left, OUT Right);
		if (!Parsed)
		{
			continue;
		}

		AllTasks.AddUnique(Left);
		AllTasks.AddUnique(Right);
		if (!WaitMap.Contains(Right))
		{
			WaitMap.Add(Right, TSet<FString>());
		}
		WaitMap[Right].Add(Left);
	}
	AllTasks.Sort(std::less<FString>());

	TArray<FString> WaitKeys;
	WaitMap.KeySort(std::less<FString>());
	WaitMap.GetKeys(OUT WaitKeys);
	auto WaitSet = TSet<FString>(WaitKeys);
	TSet<FString> RootSet;
	TArray<FString> Result;
	
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *ConcatArray(Result));
	bool SetChanged;
	do
	{
		SetChanged = false;
		for (auto Task : AllTasks)
		{
			// Check if already in root set
			if (RootSet.Contains(Task))
			{
				continue;
			}

			// Check if blocked
			if (WaitMap.Contains(Task) && WaitMap[Task].Difference(RootSet).Num() != 0)
			{
				continue;
			}

			RootSet.Add(Task);
			Result.Add(Task);
			SetChanged = true;
			break;
		}
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *ConcatArray(Result));
	} while (SetChanged);

	return ConcatArray(Result);
}

FString ADay07::CalculateResultB()
{
	return FString();
}

bool ADay07::ParseLine(FString Input, FString& OutLeft, FString& OutRight)
{
	FIntPoint Result;

	FRegexPattern Pattern(TEXT("Step (\\w) must be finished before step (\\w) can begin."));
	FRegexMatcher Matcher(Pattern, Input);

	if (Matcher.FindNext())
	{
		OutLeft = *Matcher.GetCaptureGroup(1);
		OutRight = *Matcher.GetCaptureGroup(2);
		return true;
	}
	else
	{
		return false;
	}

}

FString ADay07::ConcatArray(TArray<FString> Array)
{
	FString Text;
	for (auto Value : Array)
	{
		Text.Append(Value);
	}
	return Text;
}

