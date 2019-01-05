// Fill out your copyright notice in the Description page of Project Settings.

#include "Day08.h"

ADay08::ADay08()
{
	InputFileName = FString("Input/input08.txt");

	Data = ParseInput();
}

FString ADay08::CalculateResultA()
{
	int32 IteratorIndex = 0;
	int32 MetaSum = 0;
	IterateElements(1, IteratorIndex, MetaSum);

	// UE_LOG(LogTemp, Warning, TEXT("MetaSum = %d"), MetaSum);

	return FString::FromInt(MetaSum);
}

FString ADay08::CalculateResultB()
{
	int32 IteratorIndex = 0;
	auto Result = ValueSum(IteratorIndex);

	return FString::FromInt(Result);
}

void ADay08::IterateElements(int32 Count, int32& IteratorIndex, int32& MetaSum)
{
	for (auto Iteration = 0; Iteration < Count; ++Iteration)
	{
		// UE_LOG(LogTemp, Warning, TEXT("IteratorIndex: %d"), IteratorIndex);
		auto Children = Data[IteratorIndex++];
		auto MetaElements = Data[IteratorIndex++];
		// UE_LOG(LogTemp, Warning, TEXT("Children = %d; Meta Elements = %d"), Children, MetaElements);

		IterateElements(Children, IteratorIndex, MetaSum);

		// UE_LOG(LogTemp, Warning, TEXT("Reading %d meta elements"), MetaElements);
		for (auto Index = 0; Index < MetaElements; ++Index)
		{
			auto Meta = Data[IteratorIndex++];
			// UE_LOG(LogTemp, Warning, TEXT("Meta = %d"), Meta);
			MetaSum += Meta;
		}
	}
}

int32 ADay08::ValueSum(int32& IteratorIndex)
{
	auto Children = Data[IteratorIndex++];
	auto MetaElements = Data[IteratorIndex++];
	TArray<int32> ChildrenValues;

	for (auto Iteration = 0; Iteration < Children; ++Iteration)
	{
		ChildrenValues.Add(ValueSum(IteratorIndex));
	}

	auto Result = 0;
	for (auto Index = 0; Index < MetaElements; ++Index)
	{
		auto Meta = Data[IteratorIndex++];
		if (Children == 0)
		{
			Result += Meta;
		}
		else
		{
			if (Meta > 0 && Meta <= Children)
			{
				Result += ChildrenValues[Meta - 1];
			}
		}
	}

	return Result;
}

TArray<int32> ADay08::ParseInput()
{
	auto Lines = LoadInputLines();
	auto Line = Lines[0];
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);

	TArray<FString> NumberStrings;
	TArray<int32> Numbers;
	Line.ParseIntoArray(OUT NumberStrings, *FString(" "));

	auto Sum = 0;
	for (auto NumberString : NumberStrings)
	{
		auto Number = FCString::Atoi(*NumberString);
		Sum += Number;
		Numbers.Add(Number);
	}
	// UE_LOG(LogTemp, Warning, TEXT("Sum: %d"), Sum);

	return Numbers;
}