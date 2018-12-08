// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AOC2018GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AOC2018_API AAOC2018GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAOC2018GameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	UFUNCTION(BlueprintPure, Category = Advent)
	TArray<class ADayBase*> GetAllDays();
	
	
};
