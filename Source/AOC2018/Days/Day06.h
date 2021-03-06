// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day06.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay06 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay06();

	static int32 FindDistance(FIntPoint A, FIntPoint B);

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

	FIntPoint ParsePoint(FString Input);

	bool GetClosestPoint(TArray<FIntPoint> Points, FIntPoint Target, FIntPoint& OutClosestPoint);
	TArray<FIntPoint> GetPointsClosestToEdge(TArray<FIntPoint> Points, FIntPoint Min, FIntPoint Max);
	int32 GetTotalDistance(TArray<FIntPoint> Points, FIntPoint Target);

	int32 TotalDistanceLessThan = 0;

};