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

	return FString::Printf(TEXT("%lld"), MaxScore);
}

FString ADay09::CalculateResultB()
{
	auto MaxScore = GetMaxScore(LastMarble * 100);

	return FString::Printf(TEXT("%lld"), MaxScore);
}

int64 ADay09::GetMaxScore(int32 Marbles)
{
	double StartTime = FPlatformTime::Seconds();

	TDoubleLinkedList<int32> Board;
	Board.AddTail(0);
	auto BoardIterator = Board.GetTail();

	TMap<int32, int64> PlayerScores;
	int CurrentPlayer = 0;

	for (int Marble = 1; Marble <= Marbles; ++Marble)
	{
		if (Marble % 23 == 0)
		{
			// Move right 7 positions (or cycle)
			for (auto Iterator = 0; Iterator < 7; ++Iterator)
			{
				if (BoardIterator == Board.GetTail())
				{
					BoardIterator = Board.GetHead();
				}
				else
				{
					BoardIterator = BoardIterator->GetNextNode();
				}
			}

			// Add score
			auto BoardItem = (*BoardIterator).GetValue();
			auto OldScore = PlayerScores.Contains(CurrentPlayer) ? PlayerScores[CurrentPlayer] : 0;
			PlayerScores.Add(CurrentPlayer, OldScore + Marble + BoardItem);

			// Remove node
			if (BoardIterator == Board.GetTail())
			{
				Board.RemoveNode(BoardIterator);
				BoardIterator = Board.GetHead();
			}
			else
			{
				auto GetPrevNode = BoardIterator->GetPrevNode();
				Board.RemoveNode(BoardIterator);
				BoardIterator = GetPrevNode;
			}
		}
		else
		{
			// Move one left (or cycle)
			if (BoardIterator == Board.GetHead())
			{
				BoardIterator = Board.GetTail();
			}
			else
			{
				BoardIterator = BoardIterator->GetPrevNode();
			}

			// Insert before current and move one left
			Board.InsertNode(Marble, BoardIterator);
			BoardIterator = BoardIterator->GetPrevNode();
		}

		// UE_LOG(LogTemp, Warning, TEXT("Marble: %d; Index: %d"), Marble, CurrentIndex);

		/*
		FString DebugPrint;
		for (auto Item : Board) {
			DebugPrint.Append(FString::FromInt(Item));
			DebugPrint.Append(" ");
		}
		UE_LOG(LogTemp, Warning, TEXT("Current: %d"), (*BoardIterator).GetValue());
		UE_LOG(LogTemp, Warning, TEXT("Debug: %s"), *DebugPrint);
		*/

		CurrentPlayer = (CurrentPlayer + 1) % Players;
	}

	int64 MaxScore = 0;
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
