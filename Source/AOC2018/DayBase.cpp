// Fill out your copyright notice in the Description page of Project Settings.

#include "DayBase.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


// Sets default values
ADayBase::ADayBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADayBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ADayBase::LoadInput()
{
	auto Lines = LoadInputLines();
	FString Result;

	for (auto Line : Lines)
	{
		Result += Line;
	}

	return Result;
}

TArray<FString> ADayBase::LoadInputLines()
{
	TArray<FString> Strings;

	FFileHelper::LoadANSITextFileToStrings(*(FPaths::ProjectDir() + InputFileName), NULL, Strings);

	// Pops last element if it's empty.
	if (Strings.Num() > 0 && Strings.Last().IsEmpty())
	{
		Strings.RemoveAt(Strings.Num() - 1);
	}
	
	return Strings;
}

template<class K, class V>
K ADayBase::GetFirstKey(TMap<K, V> Map)
{
	K Default;
	TArray<K> MapKeys;
	SleepTotals.GetKeys(MapKeys);
	if (MapKeys.Num() == 0)
	{
		return Default;
	}
	return MapKeys[0];
}

template<>
int32 ADayBase::GetFirstKey(TMap<int32, int32> Map)
{
	int32 Result;
	for (auto Pair : Map)
	{
		Result = Pair.Key;
		break;
	}
	return Result;
}

FIntPoint ADayBase::GetFirstKey(TMap<FIntPoint, int32> Map)
{
	FIntPoint Result;
	for (auto Pair : Map)
	{
		Result = Pair.Key;
		break;
	}
	return Result;
}

FString ADayBase::GetResultA()
{
	auto Result = CalculateResultA();
	UE_LOG(LogTemp, Warning, TEXT("(%s) Result A: %s."), *GetClass()->GetName(), *Result);
	return Result;
}

FString ADayBase::GetResultB()
{
	auto Result = CalculateResultB();
	UE_LOG(LogTemp, Warning, TEXT("(%s) Result B: %s."), *GetClass()->GetName(), *Result);
	return Result;
}

FString ADayBase::CalculateResultA()
{
	return FString();
}

FString ADayBase::CalculateResultB()
{
	return FString();
}

