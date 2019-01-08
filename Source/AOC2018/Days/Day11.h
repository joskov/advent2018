// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day11.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay11 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay11();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;
	int32 CalculatePower(FIntPoint Point);
	int32 CalculateSquarePower(FIntPoint TopLeft, int32 SquareSize);
	int32 CalculateMaxSquareSize(int32 SquareSize, FIntPoint& OutTopLeft);
	
	int32 SerialNumber;
	int32 MaxCoordinate;
};
