// Fill out your copyright notice in the Description page of Project Settings.

#include "Day08.h"

ADay08::ADay08()
{
	InputFileName = FString("Input/input08.txt");

	Data = ParseInput();
}

FString ADay08::CalculateResultA()
{
	auto DataCount = Data.Num();
	auto NumChildren = Data[0];
	auto NumMetadata = Data[1];
	TArray<int32> MetaData;
	
	int32 IteratorIndex = 0;
	int32 MetaSum = 0;
	IterateElements(1, IteratorIndex, MetaSum);

	UE_LOG(LogTemp, Warning, TEXT("MetaSum = %d"), MetaSum);

	return FString::FromInt(1);
}

void ADay08::IterateElements(int32 Count, int32& IteratorIndex, int32& MetaSum)
{
	for (auto Iteration = 0; Iteration < Count; ++Iteration)
	{
		UE_LOG(LogTemp, Warning, TEXT("IteratorIndex: %d"), IteratorIndex);
		auto Children = Data[IteratorIndex++];
		auto MetaElements = Data[IteratorIndex++];
		UE_LOG(LogTemp, Warning, TEXT("Children = %d; Meta Elements = %d"), Children, MetaElements);

		IterateElements(Children, IteratorIndex, MetaSum);

		UE_LOG(LogTemp, Warning, TEXT("Reading %d meta elements"), MetaElements);
		for (auto Index = 0; Index < MetaElements; ++Index)
		{
			auto Meta = Data[IteratorIndex++];
			UE_LOG(LogTemp, Warning, TEXT("Meta = %d"), Meta);
			MetaSum += Meta;
		}
	}
}

FString ADay08::CalculateResultB()
{
	return FString::FromInt(2);
}

TArray<int32> ADay08::ParseInput()
{
	auto Lines = LoadInputLines();
	auto Line = Lines[0];
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);

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