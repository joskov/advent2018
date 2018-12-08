// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day01.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay01 : public ADayBase
{
	GENERATED_BODY()
	
protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

};
