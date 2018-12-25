// Fill out your copyright notice in the Description page of Project Settings.

#include "Day07.h"
#include "Internationalization/Regex.h"

ADay07::ADay07()
{
	InputFileName = FString("Input/input07.txt");
	MaxWorkers = 5;
	WaitTime = 60;

	auto Lines = LoadInputLines();
	ParseInput(Lines);
}

FString ADay07::CalculateResultA()
{
	TSet<FString> RootSet;
	TArray<FString> Result;
	
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
	int32 Step = 0;
	TSet<FString> RootSet;
	TMap<FString, int32> Workers;

	bool SetChanged;
	do
	{
		TArray<FString> Completed;
		for (auto Worker : Workers)
		{
			if (Worker.Value <= 0)
			{
				Completed.Add(Worker.Key);
			}
		}

		for (auto Task : Completed)
		{
			RootSet.Add(Task);
			Workers.Remove(Task);
		}

		SetChanged = false;
		for (auto Task : AllTasks)
		{
			// Workers are busy
			if (Workers.Num() >= MaxWorkers)
			{
				continue;
			}

			// Check if already in root set
			if (RootSet.Contains(Task))
			{
				continue;
			}

			// Working on it
			if (Workers.Contains(Task))
			{
				continue;
			}

			// Check if blocked
			if (WaitMap.Contains(Task) && WaitMap[Task].Difference(RootSet).Num() != 0)
			{
				continue;
			}

			auto FirstChar = Task.GetCharArray()[0];
			auto TimeRequired = FirstChar - TCHAR('A') + 1 + WaitTime;
			// UE_LOG(LogTemp, Warning, TEXT("Time for %s = %d"), *Task, TimeRequired);

			Workers.Add(Task, TimeRequired);
			SetChanged = true;
		}

		for (auto Worker : Workers)
		{
			Workers[Worker.Key] = Workers[Worker.Key] - 1;
		}

		// UE_LOG(LogTemp, Warning, TEXT("Second: %d, Done %s."), Step, *ConcatArray(RootSet.Array()));

		if (Workers.Num() == 0 && !SetChanged)
		{
			break;
		}

		Step += 1;
	} while (true);

	return FString::FromInt(Step);
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

void ADay07::ParseInput(TArray<FString> Input)
{
	WaitMap.Empty();
	AllTasks.Empty();

	for (auto Line : Input)
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

