// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day08.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay08 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay08();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;
	
	TArray<int32> Data;

	TArray<int32> ParseInput();

	void IterateElements(int32 Count, int32& IteratorIndex, int32& MetaSum);

};
