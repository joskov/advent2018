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

int ADay04::FindResultA()
{
	auto Lines = LoadInputLines();
	auto Logs = LogsFromLines(Lines);
	Logs.Sort();

	
	TMap<int32, int32> SleepTotals;
	TMap<int32, TArray<FSleep>> SleepLogs;
	GetSleepLogs(OUT SleepTotals, OUT SleepLogs, Logs);
	SleepTotals.ValueSort([](int a, int b) -> bool { return a > b; });

	// TODO: refactor to get the top value
	TPair<int32, int32> TopPair;
	for (auto Pair : SleepTotals)
	{
		TopPair = Pair;
		break;
	}

	TMap<int32, int32> MinutesList;
	verify(SleepLogs.Contains(TopPair.Key));

	auto TopKey = TopPair.Key;
	for (auto SleepLog : SleepLogs[TopKey])
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
		UE_LOG(LogTemp, Warning, TEXT("Key: %d, Value: %d"), MinutePair.Key, MinutePair.Value);

	}
	
	auto FilteredSleepLogs = SleepLogs[TopKey];
	TArray<int32> MinutesKeys;
	MinutesList.GetKeys(MinutesKeys);
	auto MaxMinuteKey = MinutesKeys[0];

	UE_LOG(LogTemp, Warning, TEXT("TopKey: %d. TopValue: %d. MaxMinute: %d."), TopKey, TopPair.Value, MaxMinuteKey);

	UE_LOG(LogTemp,  Warning, TEXT("Result A: %d"), MaxMinuteKey * TopKey);

	return 0;
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
	return Logs;
}

void ADay04::GetSleepLogs(TMap<int32, int32>& OutSleepTotals, TMap<int32, TArray<FSleep>>& OutSleepLogs, TArray<FGuardLog> Logs)
{
	int32 CurrentID = -1;
	FGuardTime FallAsleepTime;
	for (auto LogRecord : Logs)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogRecord.Log);

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
}

int ADay04::FindResultB()
{
	auto Lines = LoadInputLines();
	return 0;
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
