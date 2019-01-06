// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day09.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay09 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay09();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;
	
	int Players;
	int LastMarble;

};
