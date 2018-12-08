// Fill out your copyright notice in the Description page of Project Settings.

#include "AOC2018GameModeBase.h"
#include "EngineUtils.h"
#include "DayBase.h"


// Sets default values
AAOC2018GameModeBase::AAOC2018GameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAOC2018GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay!"));

	auto AllObjects = GetAllDays();
	for (auto Object : AllObjects)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Object->GetClass()->GetName());
	}
}

void AAOC2018GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("Tick!"));

}

TArray<ADayBase*> AAOC2018GameModeBase::GetAllDays()
{
	TArray<ADayBase*> DaysList;
	for (TActorIterator<ADayBase> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		DaysList.Add(*Iterator);
	}
	DaysList.Sort([](AActor& A, AActor& B) -> bool { return A.GetClass()->GetName() < B.GetClass()->GetName(); });
	return DaysList;
}

