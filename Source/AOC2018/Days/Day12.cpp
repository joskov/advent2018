// Fill out your copyright notice in the Description page of Project Settings.

#include "Day12.h"


ADay12::ADay12()
{
	InputFileName = FString("Input/input12.txt");
}

FString ADay12::CalculateResultA()
{
	ParseInput();

	auto Data = FString(InitialState);
	int32 CurrentStartIndex = 0;
	for (int I = 0; I < 20; ++I)
	{
		Data.InsertAt(0, "....");
		CurrentStartIndex -= 2;
		Data.Append("....");
		
		FString NewData;
		for (int Cursor = 0; Cursor < Data.Len() - 4; ++Cursor)
		{
			auto Key = Data.Mid(Cursor, 5);
			auto Grows = GrowMap.Contains(Key) && GrowMap[Key] == FString("#");
			NewData.Append(FString(Grows ? "#" : "."));
		}

		Data = NewData;

		// Remove leading and trailing empty pots
		while (Data.RemoveFromStart("."))
		{
			CurrentStartIndex++;
		}
		while (Data.RemoveFromEnd("."));
	}

	UE_LOG(LogTemp, Warning, TEXT("State %s; Current Start Index = %d"), *Data, CurrentStartIndex);

	int32 Result = 0;
	for (int I = 0; I < Data.Len(); ++I)
	{
		if (Data.Mid(I, 1) == FString("#"))
		{
			Result += (I + CurrentStartIndex);
		}
	}

	return FString::FromInt(Result);
}

FString ADay12::CalculateResultB()
{
	// TODO: convert the logic to make faster iterations so we can use the 50,000,000,000
	return FString::Printf(TEXT("b"));
}

void ADay12::ParseInput()
{
	auto Lines = LoadInputLines();
	auto FirstLine = Lines[0];
	FirstLine.RemoveFromStart("initial state: ");
	InitialState = FirstLine;
	UE_LOG(LogTemp, Warning, TEXT("Initial State: %s"), *InitialState);

	/// Remove first two lines
	Lines.RemoveAt(0);
	Lines.RemoveAt(0);

	GrowMap.Empty();
	for (auto Line : Lines)
	{
		GrowMap.Add(Line.Left(5), Line.Right(1));
	}

	for (auto Pair : GrowMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s -> %s"), *Pair.Key, *Pair.Value);
	}
}