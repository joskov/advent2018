// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day03.generated.h"


USTRUCT()
struct FClaim
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ID;
	
	FIntRect Rectangle;

	FString ToString()
	{
		return FString::Printf(TEXT("#%d %s"), ID, *Rectangle.ToString());
	}

	bool Intersects(FClaim& Other) const
	{
		auto Intersection = FIntRect(Rectangle);
		Intersection.Clip(Other.Rectangle);
		return Intersection.Area() != 0;
	}
};

/**
 * 
 */
UCLASS()
class AOC2018_API ADay03 : public ADayBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int FindResultA();

	UFUNCTION(BlueprintPure)
	FString FindResultB();

	ADay03();

private:
	FClaim ParseLine(FString Line);

};
