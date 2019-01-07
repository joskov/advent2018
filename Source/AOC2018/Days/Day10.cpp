// Fill out your copyright notice in the Description page of Project Settings.

#include "Day10.h"
#include "Internationalization/Regex.h"

ADay10::ADay10()
{
	InputFileName = FString("Input/input10.txt");
}

FString ADay10::CalculateResultA()
{
	auto Data = ParseInput();

	auto MinAreaTime = 0;
	auto MinArea = DisplayArea(Data, MinAreaTime);
	int32 CurrentTime = 0;
	while (true)
	{
		CurrentTime++;
		auto NewArea = DisplayArea(Data, CurrentTime);
		// UE_LOG(LogTemp, Warning, TEXT("Area = %lld (%ds)"), NewArea, CurrentTime);
		if (NewArea > MinArea) {
			break;
		}
		MinArea = NewArea;
		MinAreaTime = CurrentTime;
	}

	DisplayPoints(Data, MinAreaTime);

	return FString::FromInt(MinAreaTime);
}

FString ADay10::CalculateResultB()
{
	return FString::FromInt(2);
}

TArray<FMovingPoint> ADay10::ParseInput()
{
	auto Pattern = FRegexPattern(TEXT("position=<\\s*(-?\\d+),\\s*(-?\\d+)> velocity=<\\s*(-?\\d+),\\s*(-?\\d+)>"));
	auto Data = LoadInputLines();
	TArray<FMovingPoint> Result;

	int32 ID = 0;
	for (auto Line : Data)
	{
		auto Matcher = FRegexMatcher(Pattern, Line);
		if (Matcher.FindNext())
		{
			FMovingPoint MovingPoint;
			MovingPoint.Position.X = FCString::Atoi(*Matcher.GetCaptureGroup(1));
			MovingPoint.Position.Y = FCString::Atoi(*Matcher.GetCaptureGroup(2));
			MovingPoint.Velocity.X = FCString::Atoi(*Matcher.GetCaptureGroup(3));
			MovingPoint.Velocity.Y = FCString::Atoi(*Matcher.GetCaptureGroup(4));
			MovingPoint.ID = ID++;
			Result.Add(MovingPoint);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldn't parse row %s"), *Line);
		}
	}

	return Result;
}

void ADay10::DisplayPoints(TArray<FMovingPoint> Points, int32 SecondsPassed)
{
	if (Points.Num() == 0)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%ds"), SecondsPassed);

	auto Min = Points[0].Position + Points[0].Velocity * SecondsPassed;
	auto Max = Points[0].Position + Points[0].Velocity * SecondsPassed;
	TMap<int32, TArray<int32>> ConvertedPoints;
	// Convert points and find min and max
	for (auto Point : Points)
	{
		auto X = Point.Position.X + Point.Velocity.X * SecondsPassed;
		auto Y = Point.Position.Y + Point.Velocity.Y * SecondsPassed;
		if (X < Min.X)
		{
			Min.X = X;
		}
		if (Y < Min.Y)
		{
			Min.Y = Y;
		}
		if (X > Max.X)
		{
			Max.X = X;
		}
		if (Y > Max.Y)
		{
			Max.Y = Y;
		}
	}

	// UE_LOG(LogTemp, Warning, TEXT("Min %s, Max %s"), *Min.ToString(), *Max.ToString());

	for (auto Point : Points)
	{
		auto X = Point.Position.X + Point.Velocity.X * SecondsPassed;
		auto Y = Point.Position.Y + Point.Velocity.Y * SecondsPassed;

		if (!ConvertedPoints.Contains(X))
		{
			ConvertedPoints.Add(X);
		}
		ConvertedPoints[X].Add(Y);
	}

	for (int Y = Min.Y; Y <= Max.Y; ++Y)
	{
		FString Line;
		for (int X = Min.X; X <= Max.X; ++X)
		{
			if (ConvertedPoints.Contains(X) && ConvertedPoints[X].Contains(Y))
			{
				Line.Append("#");
			}
			else
			{
				Line.Append(".");
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);
	}
}

int64 ADay10::DisplayArea(TArray<FMovingPoint> Points, int32 SecondsPassed)
{
	if (Points.Num() == 0)
	{
		return 0;
	}

	auto Min = Points[0].Position + Points[0].Velocity * SecondsPassed;
	auto Max = Points[0].Position + Points[0].Velocity * SecondsPassed;
	// Find min and max
	for (auto Point : Points)
	{
		auto X = Point.Position.X + Point.Velocity.X * SecondsPassed;
		auto Y = Point.Position.Y + Point.Velocity.Y * SecondsPassed;
		if (X < Min.X)
		{
			Min.X = X;
		}
		if (Y < Min.Y)
		{
			Min.Y = Y;
		}
		if (X > Max.X)
		{
			Max.X = X;
		}
		if (Y > Max.Y)
		{
			Max.Y = Y;
		}
	}

	int64 Result = 1;
	Result *= (Max.X - Min.X);
	Result *= (Max.Y - Min.Y);
	return Result;
}

