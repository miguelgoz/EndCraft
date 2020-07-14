// Fill out your copyright notice in the Description page of Project Settings.


#include "NoisePerl.h"
#include "Math/UnrealMathUtility.h"

NoisePerl::NoisePerl()
{
}

NoisePerl::~NoisePerl()
{
}
TArray<TArray<float>*> NoisePerl::GenerateNoiseMap(int MapWidth, int MapHeight, float Scale)
{
	TArray<TArray<float>*> ContentNoise;
	ContentNoise.SetNum(MapHeight);

	if (Scale <= 0.0f)
	{
		Scale = 0.0001f;
	}
	
	for (int y = 0; y < MapHeight; y++)
	{
		TArray<float>* ContentMap = new TArray<float>();
		ContentMap->SetNum(MapWidth);

		ContentNoise.Add(ContentMap);

		for (int x = 0; x < MapWidth; x++)
		{
			float SampleX = ((float)x) / Scale;
			float SampleY = ((float)y) / Scale;
			const FVector2D CurrentLocation = FVector2D((x + 0) / 1, (y + 0) / 1);
			const float PerlinValue = FMath::PerlinNoise2D(CurrentLocation) * 1;
			ContentMap->Add(PerlinValue);
		}
	}

	return ContentNoise;
}
