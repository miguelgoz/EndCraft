// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include "Noise/NoisePerl.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GenerateMap()
{
	TArray<TArray<float>*>* NoiseMap = NoisePerl::GenerateNoiseMap(MapWidth, MapHeight, Seed, NoiseScale, Blocks.Num(), Persistance, Lacunarity);

	DrawNoiseMap(NoiseMap);
}

void AMapGenerator::DrawNoiseMap(TArray<TArray<float>*>* NoiseMap)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	for (int y = 0; y != NoiseMap->Num(); y++)
	{
		TArray<float>* ValuesX = (*NoiseMap)[y];
		for (int x = 0; x != ValuesX->Num(); x++)
		{		
			float Value = (*ValuesX)[x];

			TSubclassOf<ABlockBase> TypeOfBlock = Blocks[(int)Value];

			FVector Location((float)x*16.0f, (float)y * 16.0f, 0.0f);

			FActorSpawnParameters SpawnInfo;
			GetWorld()->SpawnActor<ABlockBase>(TypeOfBlock, Location, Rotation, SpawnInfo);
		}
	}
}