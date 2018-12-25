// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day07.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API ADay07 : public ADayBase
{
	GENERATED_BODY()

public:
	ADay07();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

	static bool ParseLine(FString Input, FString& OutLeft, FString& OutRight);

	static FString ConcatArray(TArray<FString> Array);

};
