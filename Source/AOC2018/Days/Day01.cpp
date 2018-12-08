// Fill out your copyright notice in the Description page of Project Settings.

#include "Day01.h"



FString ADay01::CalculateResultA()
{
	int Result = 0;
	auto Lines = LoadInputLines();
	for (auto Line : Lines)
	{
		Result += FCString::Atoi(*Line);
	}

	return FString::FromInt(Result);
}

FString ADay01::CalculateResultB()
{
	int Frequency = 0;
	bool FoundDuplicate = false;
	auto Lines = LoadInputLines();
	TArray<int> FrequencyList;

	while (!FoundDuplicate)
	{
		for (auto Line : Lines)
		{
			auto OldFrequency = Frequency;
			auto LineInt = FCString::Atoi(*Line);
			Frequency += LineInt;

			// UE_LOG(LogTemp, Warning, TEXT("%d, %s, %d (Old, Add, New)"), OldFrequency, *Line, Frequency);

			if (FrequencyList.Contains(Frequency))
			{
				FoundDuplicate = true;
				break;
			}

			FrequencyList.Add(Frequency);
		}

		// UE_LOG(LogTemp, Warning, TEXT("%d"), Frequency);
	}

	return FString::FromInt(Frequency);
}
