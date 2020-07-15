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
	
	float MaxNoiseHeight = std::numeric_limits<float>::max();
	float MinNoiseHeight = std::numeric_limits<float>::min();

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
				float SampleX = float(((float)x- MapWidth) / Scale * Frequency) + Seed;
				float SampleY = float(((float)y- MapHeight) / Scale * Frequency) + Seed;

				FVector2D CurrentLocation = FVector2D(SampleX, SampleY);
				float PerlinValue = FMath::PerlinNoise2D(CurrentLocation) * 2.0f * -1.0f;
				
				NoiseHeight += PerlinValue * Amplitude;
				Amplitude *= Persistance;
				Frequency *= Lacunarity;



				

				
			}

			if (NoiseHeight > MaxNoiseHeight)
			{
				NoiseHeight = MaxNoiseHeight;
			}
			else if (NoiseHeight < MinNoiseHeight)
			{
				NoiseHeight = MinNoiseHeight;
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
			float NewNoiseHeightLerp = UKismetMathLibrary::InverseLerp(0.000000000000000f, 1.000000000000000000f, NoiseHeight);
			if (NewNoiseHeightLerp > 1.0f) 
			{
				NewNoiseHeightLerp = 1.0f;
			}
			else if (NewNoiseHeightLerp < 0.0f)
			{
				NewNoiseHeightLerp = 0.0f;
			}
			(*ContentMap)[x] = NewNoiseHeightLerp;

			UE_LOG(LogTemp, Warning, TEXT("Value = %f"), NewNoiseHeightLerp);
		}
	}

	return ContentNoise;
}
