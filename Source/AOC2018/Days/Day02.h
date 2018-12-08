// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day02.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay02 : public ADayBase
{
	GENERATED_BODY()
	
public:
	ADay02();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

};
