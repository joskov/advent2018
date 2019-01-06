// Fill out your copyright notice in the Description page of Project Settings.

#include "Day09.h"

ADay09::ADay09()
{
	// Players = 9;
	// LastMarble = 25;
	// Players = 30;
	// LastMarble = 5807;
	Players = 416;
	LastMarble = 71975;
}

FString ADay09::CalculateResultA()
{
	auto MaxScore = GetMaxScore(LastMarble);

	return FString::FromInt(MaxScore);
}

FString ADay09::CalculateResultB()
{
	auto MaxScore = GetMaxScore(LastMarble * 3);

	return FString::FromInt(MaxScore);
}

int32 ADay09::GetMaxScore(int Marbles)
{
	double StartTime = FPlatformTime::Seconds();

	TArray<int> Board;
	TMap<int, int32> PlayerScores;
	Board.Add(0);
	int CurrentIndex = 0;
	int CurrentPlayer = 0;

	for (int Marble = 1; Marble <= Marbles; ++Marble)
	{
		if (Marble % 23 == 0)
		{
			// UE_LOG(LogTemp, Warning, TEXT("Add Score: %d"), Marble);
			CurrentIndex = (CurrentIndex - 7) % Board.Num();
			if (CurrentIndex < 0)
			{
				CurrentIndex = Board.Num() + CurrentIndex;
			}

			// Add score
			auto OldScore = PlayerScores.Contains(CurrentPlayer) ? PlayerScores[CurrentPlayer] : 0;
			PlayerScores.Add(CurrentPlayer, OldScore + Marble + Board[CurrentIndex]);

			Board.RemoveAt(CurrentIndex);
			CurrentIndex = CurrentIndex % Board.Num();
		}
		else
		{
			CurrentIndex = ((CurrentIndex + 1) % Board.Num()) + 1;
			Board.Insert(Marble, CurrentIndex);
		}

		// UE_LOG(LogTemp, Warning, TEXT("Marble: %d; Index: %d"), Marble, CurrentIndex);

		/*
		FString DebugPrint;
		for (auto Marble : Board)
		{
			DebugPrint.Append(FString::FromInt(Marble));
			DebugPrint.Append(" ");
		}
		UE_LOG(LogTemp, Warning, TEXT("Debug: %s"), *DebugPrint);
		*/

		CurrentPlayer = (CurrentPlayer + 1) % Players;
	}

	int MaxScore = 0;
	for (auto ScorePair : PlayerScores)
	{
		if (ScorePair.Value > MaxScore)
		{
			MaxScore = ScorePair.Value;
		}
	}

	double EndTime = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("Calculation time %f.2s"), EndTime - StartTime);

	return MaxScore;
}
