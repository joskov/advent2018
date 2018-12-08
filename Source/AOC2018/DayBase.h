// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayBase.generated.h"

struct FIntIntPair
{
	int32 A;
	int32 B;

	FIntIntPair(int32 A, int32 B) : A(A), B(B) {};
};

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

	// template<class K, class V>
	// static TPair<K, V> GetFirstPair(TMap<K, V> Map);
	// TODO: refactor to a template
	static int32 GetFirstKey(TMap<int32, int32> Map);

	UFUNCTION(BlueprintCallable, Category = Advent)
	FString GetResultA();

	UFUNCTION(BlueprintCallable, Category = Advent)
	FString GetResultB();

protected:
	FString InputFileName = FString("Input/input01.txt");

	virtual FString CalculateResultA();

	virtual FString CalculateResultB();

};
