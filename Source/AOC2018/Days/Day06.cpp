// Fill out your copyright notice in the Description page of Project Settings.

#include "Day06.h"
#include "Internationalization/Regex.h"


ADay06::ADay06()
{
	InputFileName = FString("Input/input06.txt");
	TotalDistanceLessThan = 10000;
}

FString ADay06::CalculateResultA()
{
	auto Lines = LoadInputLines();
	if (Lines.Num() == 0) { return "Error"; }

	TArray<FIntPoint> Points;
	for (auto Line : Lines)
	{
		auto Point = ParsePoint(Line);
		Points.Add(Point);
	}

	
	FIntPoint Min = Points[0];
	FIntPoint Max = Points[0];
	for (auto Point : Points)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Checking Point: %s"), *Point.ToString());
		Min.X = FMath::Min(Min.X, Point.X);
		Min.Y = FMath::Min(Min.Y, Point.Y);
		Max.X = FMath::Max(Max.X, Point.X);
		Max.Y = FMath::Max(Max.Y, Point.Y);
	}
	// UE_LOG(LogTemp, Warning, TEXT("Min: %s, Max: %s"), *Min.ToString(), *Max.ToString());

	TMap<FIntPoint, int32> Totals;
	for (auto X = Min.X; X < Max.X; ++X)
	{
		for (auto Y = Min.Y; Y < Max.Y; ++Y)
		{
			FIntPoint ClosestPoint;
			auto Found = GetClosestPoint(Points, FIntPoint(X, Y), ClosestPoint);
			if (!Found)
			{
				continue;
			}

			if (Totals.Contains(ClosestPoint))
			{
				Totals.Add(ClosestPoint, Totals[ClosestPoint] + 1);
			}
			else
			{
				Totals.Add(ClosestPoint, 1);
			}
		}
	}

	auto OutsidePoints = GetPointsClosestToEdge(Points, Min, Max);
	for (auto Point : OutsidePoints)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *Point.ToString());
		Totals.Remove(Point);
	}

	for (auto Total : Totals)
	{
		auto Point = Total.Key;
		// UE_LOG(LogTemp, Warning, TEXT("(%d:%d) = %d"), Point.X, Point.Y, Total.Value);
	}
	Totals.ValueSort(std::greater<int32>());
	auto FirstKey = GetFirstKey(Totals);

	return FString::FromInt(Totals[FirstKey]);
}

FString ADay06::CalculateResultB()
{
	auto Lines = LoadInputLines();
	if (Lines.Num() == 0) { return "Error"; }

	TArray<FIntPoint> Points;
	for (auto Line : Lines)
	{
		auto Point = ParsePoint(Line);
		Points.Add(Point);
	}

	FIntPoint Min = Points[0];
	FIntPoint Max = Points[0];
	for (auto Point : Points)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Checking Point: %s"), *Point.ToString());
		Min.X = FMath::Min(Min.X, Point.X);
		Min.Y = FMath::Min(Min.Y, Point.Y);
		Max.X = FMath::Max(Max.X, Point.X);
		Max.Y = FMath::Max(Max.Y, Point.Y);
	}

	TArray<FIntPoint> ResultPoints;
	for (auto X = Min.X; X < Max.X; ++X)
	{
		for (auto Y = Min.Y; Y < Max.Y; ++Y)
		{
			int32 TotalDistance = 0;
			auto Target = FIntPoint(X, Y);
			for (auto Point : Points)
			{
				auto Distance = FindDistance(Point, Target);
				// UE_LOG(LogTemp, Warning, TEXT("Point(%s) Target(%s) Distance(%d)"), *Point.ToString(), *Target.ToString(), Distance);
				TotalDistance += Distance;
			}
			// UE_LOG(LogTemp, Warning, TEXT("Target(%s) TotalDistance(%d)"), *Target.ToString(), TotalDistance);
			if (TotalDistance < TotalDistanceLessThan)
			{
				ResultPoints.Add(Target);
			}
		}
	}

	return FString::FromInt(ResultPoints.Num());
}

bool ADay06::GetClosestPoint(TArray<FIntPoint> Points, FIntPoint Target, FIntPoint& OutClosestPoint)
{
	TMap<FIntPoint, int32> RangesMap;
	for (auto Point : Points)
	{
		RangesMap.Add(Point, FindDistance(Point, Target));
	}
	RangesMap.ValueSort(std::less<int32>());

	auto FirstKey = GetFirstKey(RangesMap);

	TArray<FIntPoint> RangesKeys;
	RangesMap.GetKeys(RangesKeys);

	// The target is closer to two points
	if ((RangesMap.Num() > 1) && (RangesMap[RangesKeys[0]] == RangesMap[RangesKeys[1]]))
	{
		return false;
	}
	
	OutClosestPoint = RangesKeys[0];
	return true;
}

int32 ADay06::FindDistance(FIntPoint A, FIntPoint B)
{
	return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

int32 ADay06::GetTotalDistance(TArray<FIntPoint> Points, FIntPoint Target)
{
	int32 TotalDistance = 0;
	for (auto Point : Points)
	{
		TotalDistance += FMath::Abs(Point.X - Target.X) + FMath::Abs(Point.Y - Target.Y);
	}
	return TotalDistance;
}

TArray<FIntPoint> ADay06::GetPointsClosestToEdge(TArray<FIntPoint> Points, FIntPoint Min, FIntPoint Max)
{
	TArray<FIntPoint> Result;
	TArray<FIntPoint> EdgePoints;
	for (auto X = Min.X; X < Max.X; ++X)
	{
		EdgePoints.Add(FIntPoint(X, Min.Y));
		EdgePoints.Add(FIntPoint(X, Max.Y));
	}
	for (auto Y = Min.Y; Y < Max.Y; ++Y)
	{
		EdgePoints.Add(FIntPoint(Min.X, Y));
		EdgePoints.Add(FIntPoint(Max.X, Y));
	}

	for (auto EdgePoint : EdgePoints)
	{
		FIntPoint ClosestPoint;
		auto Found = GetClosestPoint(Points, EdgePoint, ClosestPoint);
		if (Found)
		{
			Result.AddUnique(ClosestPoint);
		}
	}

	return Result;
}

FIntPoint ADay06::ParsePoint(FString Input)
{
	FIntPoint Result;

	FRegexPattern Pattern(TEXT("(\\d+), (\\d+)"));
	FRegexMatcher Matcher(Pattern, Input);

	if (Matcher.FindNext())
	{
		Result.X = FCString::Atoi(*Matcher.GetCaptureGroup(1));
		Result.Y = FCString::Atoi(*Matcher.GetCaptureGroup(2));
	}

	return Result;
}
