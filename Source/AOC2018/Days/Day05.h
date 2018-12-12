// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day05.generated.h"


/**
 * 
 */
UCLASS()
class AOC2018_API ADay05 : public ADayBase
{
	GENERATED_BODY()
	
public:
	ADay05();

protected:
	virtual FString CalculateResultA() override;
	virtual FString CalculateResultB() override;

	int ReduceChain(TArray<TCHAR> Chain);
	TArray<TCHAR> RemoveChars(TArray<TCHAR> InChars, TCHAR Char);

	static FString GlueChars(TArray<TCHAR> Chars);
};
