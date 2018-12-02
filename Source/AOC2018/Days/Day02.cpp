// Fill out your copyright notice in the Description page of Project Settings.

#include "Day02.h"
#include "Misc/Char.h"


ADay02::ADay02()
{
	InputFileName = FString("Input/input02.txt");
}

int ADay02::FindResultA()
{
	int Doubles = 0;
	int Tripples = 0;
	auto Lines = LoadInputLines();

	for (auto Line : Lines)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s 2x%d 3x%d"), *Line, Doubles, Tripples);
		TMap<TCHAR, int32> CharMap;

		for (auto Char : Line.GetCharArray())
		{
			if (!CharMap.Contains(Char))
			{
				CharMap.Add(Char, 0);
			}
			CharMap.Add(Char, CharMap[Char] + 1);
		}

		if (CharMap.FindKey(2) != nullptr)
		{
			Doubles += 1;
		}
		if (CharMap.FindKey(3) != nullptr)
		{
			Tripples += 1;
		}
	}

	return Doubles * Tripples;
}

FString ADay02::FindResultB()
{
	auto Lines = LoadInputLines();
	FString Result;

	// TODO: refactor the brute force to a more elegant solution
	for (auto Line1 : Lines)
	{
		for (auto Line2 : Lines)
		{
			int Differences = 0;
			Result = FString();

			for (int i = 0; i < Line1.Len(); i++)
			{
				if (Line1[i] == Line2[i])
				{
					Result.AppendChar(Line1[i]);
				}
				else
				{
					Differences += 1;
				}
				if (Differences > 1)
				{
					break;
				}
			}

			if (Differences == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *Result);
				break;
			}
		}

	}
	return Result;
}
