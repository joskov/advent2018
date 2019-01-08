// Fill out your copyright notice in the Description page of Project Settings.

#include "Day11.h"

ADay11::ADay11()
{
	SerialNumber = 5535;
	MaxCoordinate = 300;
}

FString ADay11::CalculateResultA()
{
	auto SquareSize = 3;
	FIntPoint MaxPowerPoint;
	auto MaxPower = CalculateMaxSquareSize(SquareSize, OUT MaxPowerPoint);

	UE_LOG(LogTemp, Warning, TEXT("Max Power is %d (%d,%d)"), MaxPower, MaxPowerPoint.X, MaxPowerPoint.Y);
	return FString::Printf(TEXT("%d,%d"), MaxPowerPoint.X, MaxPowerPoint.Y);
}

FString ADay11::CalculateResultB()
{
	FIntPoint MaxPowerPoint;
	int32 MaxPowerSquareSize = 1;
	auto MaxPower = CalculateMaxSquareSize(MaxPowerSquareSize, OUT MaxPowerPoint);
	/// TODO: make it so that you get to 300
	for (auto NewSquareSize = 2; NewSquareSize <= 15; ++NewSquareSize)
	{
		FIntPoint NewPowerPoint;
		auto NewPower = CalculateMaxSquareSize(NewSquareSize, OUT NewPowerPoint);
		if (NewPower > MaxPower)
		{
			MaxPower = NewPower;
			MaxPowerPoint = NewPowerPoint;
			MaxPowerSquareSize = NewSquareSize;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Max Power is %d (%d,%d) with square size %d"), MaxPower, MaxPowerPoint.X, MaxPowerPoint.Y, MaxPowerSquareSize);
	return FString::Printf(TEXT("%d,%d,%d"), MaxPowerPoint.X, MaxPowerPoint.Y, MaxPowerSquareSize);
}

int32 ADay11::CalculatePower(FIntPoint Point)
{
	auto RackID = Point.X + 10;
	auto StartPower = RackID * Point.Y;
	auto AddSerial = StartPower + SerialNumber;
	auto MultiplyRackID = AddSerial * RackID;
	auto Hundreds = (MultiplyRackID / 100) % 10;
	auto Result = Hundreds - 5;
	return Result;
}

int32 ADay11::CalculateSquarePower(FIntPoint TopLeft, int32 SquareSize)
{
	auto TotalPower = 0;
	for (auto X = 0; X < SquareSize; ++X)
	{
		for (auto Y = 0; Y < SquareSize; ++Y)
		{
			auto Delta = FIntPoint(X, Y);
			auto Power = CalculatePower(TopLeft + Delta);
			TotalPower += Power;
		}
	}
	return TotalPower;
}

int32 ADay11::CalculateMaxSquareSize(int32 SquareSize, FIntPoint & OutTopLeft)
{
	auto MaxPowerPoint = FIntPoint(1, 1);
	auto MaxPower = CalculateSquarePower(MaxPowerPoint, SquareSize);
	for (auto Y = 1; Y <= MaxCoordinate - SquareSize; ++Y)
	{
		for (auto X = 1; X <= MaxCoordinate - SquareSize; ++X)
		{
			auto Point = FIntPoint(X, Y);
			auto TotalPower = CalculateSquarePower(Point, SquareSize);
			if (TotalPower > MaxPower)
			{
				MaxPower = TotalPower;
				MaxPowerPoint = Point;
			}
		}
	}
	OutTopLeft = MaxPowerPoint;
	return MaxPower;
}
