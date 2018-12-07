// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayBase.h"
#include "Day04.generated.h"


struct FGuardTime
{
	int32 Year;
	int32 Month;
	int32 Day;

	int32 Hour;
	int32 Minute;

	FString ToString()
	{
		return FString::Printf(TEXT("%d.%d.%d %d:%d"), Year, Month, Day, Hour, Minute);
	}

	int32 Compare(const FGuardTime& Other) const
	{
		if (Year != Other.Year)
		{
			return Year - Other.Year;
		}
		if (Month != Other.Month)
		{
			return Month - Other.Month;
		}
		if (Day != Other.Day)
		{
			return Day - Other.Day;
		}
		if (Hour != Other.Hour)
		{
			return Hour - Other.Hour;
		}
		if (Minute != Other.Minute)
		{
			return Minute - Other.Minute;
		}
		return 0;
	}
};

struct FGuardLog
{
	FGuardTime TimeStamp;
	FString Log;

	int32 Compare(const FGuardLog& Other) const
	{
		return TimeStamp.Compare(Other.TimeStamp);
	}

	bool operator<(const FGuardLog& Other) const
	{
		return Compare(Other) < 0;
	}
};

struct FSleep
{
	int32 StartMinute;
	int32 EndMinute;

	FSleep(int32 StartMinute, int32 EndMinute) : StartMinute(StartMinute), EndMinute(EndMinute) {};

	FString ToString()
	{
		return FString::Printf(TEXT("%d - %d"), StartMinute, EndMinute);
	}
};

/**
 * 
 */
UCLASS()
class AOC2018_API ADay04 : public ADayBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int FindResultA();

	UFUNCTION(BlueprintPure)
	int FindResultB();

	ADay04();

protected:
	FGuardTime ParseTime(FString Line);

	TArray<FGuardLog> LogsFromLines(TArray<FString> Lines);
	
	void GetSleepLogs(TMap<int32, int32>& OutSleepTotals, TMap<int32, TArray<FSleep>>& OutSleepLogs, TArray<FGuardLog> Logs);

	TMap<int32, int32> GetMinutesList(TArray<FSleep> SleepLog);

	TTuple<int32, int32> GetMaxMinute(TArray<FSleep> SleepLog);

};
