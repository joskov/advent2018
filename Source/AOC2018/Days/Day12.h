// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day12.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay12 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay12();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

	void ParseInput();

	FString InitialState;
	TMap<FString, FString> GrowMap;
	
};
