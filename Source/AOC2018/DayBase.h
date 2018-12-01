// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayBase.generated.h"

UCLASS()
class AOC2018_API ADayBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayBase();

protected:
	// TODO: remove / not needed
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// TODO: remove / not needed
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = Input)
	FString LoadInput();

	UFUNCTION(BlueprintPure, Category = Input)
	TArray<FString> LoadInputLines();

protected:
	FString InputFileName = FString("Input/input01.txt");
	
};
