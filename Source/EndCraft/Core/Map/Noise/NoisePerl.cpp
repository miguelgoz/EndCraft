// Fill out your copyright notice in the Description page of Project Settings.


#include "NoisePerl.h"
#include <limits>
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

NoisePerl::NoisePerl()
{
}

NoisePerl::~NoisePerl()
{
}
TArray<TArray<float>*>* NoisePerl::GenerateNoiseMap(int MapWidth, int MapHeight, int Seed, float Scale, int Octaves, float Persistance, float Lacunarity)
{
	TArray<TArray<float>*>* ContentNoise = new TArray<TArray<float>*>();
	

	if (Scale <= 0.0f)
	{
		Scale = 0.0001f;
	}
	
	float MaxNoiseHeight = std::numeric_limits<float>::min();
	float MinNoiseHeight = std::numeric_limits<float>::max();

	float HalfWidth = MapWidth / 2.0f;
	float HalfHeight = MapHeight / 2.0f;

	for (int y = 0; y < MapHeight; y++)
	{
		TArray<float>* ContentMap = new TArray<float>();

		ContentNoise->Add(ContentMap);

		for (int x = 0; x < MapWidth; x++)
		{
			float Amplitude = 1.0f;
			float Frequency = 1.0f;
			float NoiseHeight = 0.0f;

			for (int i = 0; i < Octaves; i++)
			{
				float SampleX = (float)x;
				float SampleY = (float)y;
				SampleX = (SampleX - MapWidth) / Scale * Frequency + Seed;
				SampleY = (SampleY - MapHeight) / Scale * Frequency + Seed;

				FVector2D CurrentLocation = FVector2D(SampleX, SampleY);
				float PerlinValue = FMath::PerlinNoise2D(CurrentLocation) * 2.0f - 1.0f;
				
				NoiseHeight += PerlinValue * Amplitude;
				Amplitude *= Persistance;
				Frequency *= Lacunarity;	

				
			}

			if (NoiseHeight > MaxNoiseHeight)
			{
				MaxNoiseHeight = NoiseHeight;
			}
			else if (NoiseHeight < MinNoiseHeight)
			{
				MinNoiseHeight = NoiseHeight;
			}
			ContentMap->Add(NoiseHeight);
		}
	}

	for (int y = 0; y < MapHeight; y++)
	{
		TArray<float>* ContentMap = (*ContentNoise)[y];
		for (int x = 0; x < MapWidth; x++)
		{
			float NoiseHeight = (*ContentMap)[x];
			float NewNoiseHeightLerp = UKismetMathLibrary::InverseLerp(MinNoiseHeight, MaxNoiseHeight, NoiseHeight);
		
			(*ContentMap)[x] = NewNoiseHeightLerp;

			UE_LOG(LogTemp, Warning, TEXT("Value = %f"), NewNoiseHeightLerp);
		}
	}

	return ContentNoise;
}
