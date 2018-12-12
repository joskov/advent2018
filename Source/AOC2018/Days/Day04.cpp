// Fill out your copyright notice in the Description page of Project Settings.

#include "Day04.h"
#include "Misc/Char.h"
#include "Internationalization/Regex.h"
#include "Math/IntRect.h"
#include "Kismet/KismetMathLibrary.h"


ADay04::ADay04()
{
	InputFileName = FString("Input/input04.txt");
}

TTuple<int32, int32> ADay04::GetMaxMinute(TArray<FSleep> SleepLog)
{
	auto MinutesList = GetMinutesList(SleepLog);
	auto FirstKey = ADayBase::GetFirstKey(MinutesList);
	auto MaxTuple = TTuple<int32, int32>(FirstKey, *MinutesList.Find(FirstKey));
	return MaxTuple;
}

TArray<FGuardLog> ADay04::LogsFromLines(TArray<FString> Lines)
{
	TArray<FGuardLog> Logs;
	for (auto Line : Lines)
	{
		auto TimeString = Line.RightChop(1).Left(16);
		FGuardLog Log;
		Log.TimeStamp = ParseTime(Line);
		Log.Log = Line;
		Logs.Add(Log);
	}
	Logs.Sort();
	return Logs;
}

void ADay04::GetSleepLogs(TMap<int32, int32>& OutSleepTotals, TMap<int32, TArray<FSleep>>& OutSleepLogs, TArray<FGuardLog> Logs)
{
	int32 CurrentID = -1;
	FGuardTime FallAsleepTime;
	for (auto LogRecord : Logs)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *LogRecord.Log);

		if (LogRecord.Log.Contains("begins shift"))
		{
			CurrentID = FCString::Atoi(*LogRecord.Log.RightChop(LogRecord.Log.Find("#") + 1));
		}
		if (LogRecord.Log.Contains("falls asleep"))
		{
			FallAsleepTime = LogRecord.TimeStamp;
		}
		if (LogRecord.Log.Contains("wakes up"))
		{
			auto CurrentTime = LogRecord.TimeStamp;
			auto TimeSlept = CurrentTime.Minute - FallAsleepTime.Minute;
			auto OldTime = OutSleepTotals.FindOrAdd(CurrentID);
			OutSleepTotals.Add(CurrentID, OldTime + TimeSlept);
			auto SleepLog = FSleep(FallAsleepTime.Minute, CurrentTime.Minute);
			// UE_LOG(LogTemp, Warning, TEXT("#%d %d %s - %s"), CurrentID, TimeSlept, *FallAsleepTime.ToString(), *CurrentTime.ToString());
			// UE_LOG(LogTemp, Warning, TEXT("%s"), *SleepLog.ToString());

			auto LogArray = OutSleepLogs.Find(CurrentID);
			if (LogArray)
			{
				(*LogArray).Add(SleepLog);
			}
			else
			{
				OutSleepLogs.Add(CurrentID, TArray<FSleep>());
				(*OutSleepLogs.Find(CurrentID)).Add(SleepLog);
			}
		}
	}

	OutSleepTotals.ValueSort([](int a, int b) -> bool { return a > b; });
}

TMap<int32, int32> ADay04::GetMinutesList(TArray<FSleep> SleepLogs)
{
	TMap<int32, int32> MinutesList;
	for (auto SleepLog : SleepLogs)
	{
		for (auto Minute = SleepLog.StartMinute; Minute < SleepLog.EndMinute; Minute++)
		{
			auto OldMinute = MinutesList.FindOrAdd(Minute);
			MinutesList.Add(Minute, OldMinute + 1);
		}
	}

	MinutesList.ValueSort([](int a, int b) -> bool { return a > b; });

	for (auto MinutePair : MinutesList)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Key: %d, Value: %d"), MinutePair.Key, MinutePair.Value);
	}

	return MinutesList;
}

FGuardTime ADay04::ParseTime(FString Line)
{
	FGuardTime Result;

	Result.Year = FCString::Atoi(*Line.RightChop(1).Left(4));
	Result.Month = FCString::Atoi(*Line.RightChop(6).Left(2));
	Result.Day = FCString::Atoi(*Line.RightChop(9).Left(2));
	Result.Hour = FCString::Atoi(*Line.RightChop(12).Left(2));
	Result.Minute = FCString::Atoi(*Line.RightChop(15).Left(2));

	return Result;
}

FString ADay04::CalculateResultA()
{
	auto Lines = LoadInputLines();
	auto Logs = LogsFromLines(Lines);

	TMap<int32, int32> SleepTotals;
	TMap<int32, TArray<FSleep>> SleepLogs;
	GetSleepLogs(OUT SleepTotals, OUT SleepLogs, Logs);

	auto TopKey = ADayBase::GetFirstKey(SleepTotals);
	if (!ensure(SleepLogs.Contains(TopKey))) { return FString(); }

	auto FilteredSleepLogs = SleepLogs[TopKey];
	auto MinutesList = GetMinutesList(FilteredSleepLogs);
	auto MaxMinuteKey = ADayBase::GetFirstKey(MinutesList);

	UE_LOG(LogTemp, Warning, TEXT("TopKey: %d. MaxMinute: %d."), TopKey, MaxMinuteKey);

	UE_LOG(LogTemp, Warning, TEXT("Result A: %d"), MaxMinuteKey * TopKey);

	return FString::FromInt(MaxMinuteKey * TopKey);
}

FString ADay04::CalculateResultB()
{
	auto Lines = LoadInputLines();
	auto Logs = LogsFromLines(Lines);

	TMap<int32, int32> SleepTotals; // We don't need them here
	TMap<int32, TArray<FSleep>> SleepLogs;
	GetSleepLogs(OUT SleepTotals, OUT SleepLogs, Logs);

	TTuple<int32, int32> CurrentBest;
	int32 CurrentBestID;
	for (auto SleepLog : SleepLogs)
	{
		auto MaxMinute = GetMaxMinute(SleepLog.Value);
		UE_LOG(LogTemp, Warning, TEXT("Guard #%d. MaxMinute: %d. MaxTimes: %d."), SleepLog.Key, MaxMinute.Key, MaxMinute.Value);

		if (MaxMinute.Value > CurrentBest.Value)
		{
			CurrentBest = MaxMinute;
			CurrentBestID = SleepLog.Key;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Result B: %d"), CurrentBest.Key * CurrentBestID);

	return FString::FromInt(CurrentBest.Key * CurrentBestID);
}
