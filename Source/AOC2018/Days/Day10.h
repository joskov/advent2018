// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day10.generated.h"

struct FMovingPoint
{
	FIntPoint Position;
	FIntPoint Velocity;
	int32 ID;

	FString ToString()
	{
		return FString::Printf(TEXT("#%d Position %s. Velocity %s."), ID, *Position.ToString(), *Velocity.ToString());
	}
};

/**
 * 
 */
UCLASS()
class AOC2018_API ADay10 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay10();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

	TArray<FMovingPoint> ParseInput();

	void DisplayPoints(TArray<FMovingPoint> Points, int32 SecondsPassed);

	int64 DisplayArea(TArray<FMovingPoint> Points, int32 SecondsPassed);

};
