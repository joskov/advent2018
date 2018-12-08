// Fill out your copyright notice in the Description page of Project Settings.

#include "Day03.h"
#include "Misc/Char.h"
#include "Internationalization/Regex.h"
#include "Math/IntRect.h"


ADay03::ADay03()
{
	InputFileName = FString("Input/input03.txt");
}

FClaim ADay03::ParseLine(FString Line)
{
	FClaim Result;

	FRegexPattern Pattern(TEXT("#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)"));
	FRegexMatcher Matcher(Pattern, Line);

	if (Matcher.FindNext())
	{
		auto ID = FCString::Atoi(*Matcher.GetCaptureGroup(1));
		auto Left = FCString::Atoi(*Matcher.GetCaptureGroup(2));
		auto Top = FCString::Atoi(*Matcher.GetCaptureGroup(3));
		auto Width = FCString::Atoi(*Matcher.GetCaptureGroup(4));
		auto Height = FCString::Atoi(*Matcher.GetCaptureGroup(5));
		Result.ID = ID;
		Result.Rectangle = FIntRect(Left, Top, Left + Width, Top + Height);
	}

	return Result;
}

FString ADay03::CalculateResultA()
{
	auto Lines = LoadInputLines();
	TArray<FClaim> AddedRectangles;
	TArray<FIntRect> Overlapped;
	FString Result;

	for (auto Line : Lines)
	{
		auto Parsed = ParseLine(Line);

		for (auto Compare : AddedRectangles)
		{
			auto Intersection = FIntRect(Compare.Rectangle);
			Intersection.Clip(Parsed.Rectangle);

			if (Intersection.Area() != 0)
			{
				Overlapped.Add(Intersection);
			}
		}
		AddedRectangles.Add(Parsed);
	}

	TSet<FIntPoint> OverlappedPoints;
	for (auto Overlap : Overlapped)
	{
		for (auto X = Overlap.Min.X; X < Overlap.Max.X; X++)
		{
			for (auto Y = Overlap.Min.Y; Y < Overlap.Max.Y; Y++)
			{
				OverlappedPoints.Add(FIntPoint(X, Y));
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Overlapped Points: %d"), OverlappedPoints.Num());
	return FString::FromInt(OverlappedPoints.Num());
}

FString ADay03::CalculateResultB()
{
	auto Lines = LoadInputLines();
	TArray<FClaim> Claims;
	for (auto Line : Lines)
	{
		Claims.Add(ParseLine(Line));
	}


	for (auto Claim : Claims)
	{
		auto Predicate = [Claim](FClaim Item) -> bool { return (Claim.ID != Item.ID) && Claim.Intersects(Item); };
		auto IntersectionFound = Claims.ContainsByPredicate(Predicate);
		if (!IntersectionFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Claim with ID %d does not overlap with any other claim."), Claim.ID);
			return FString::FromInt(Claim.ID);
		}
	}

	return FString();
}
