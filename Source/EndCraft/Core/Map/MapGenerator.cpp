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
	InitializeBlocks();
	GenerateMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMapGenerator::InitializeBlocks()
{
	FActorSpawnParameters SpawnInfo;
	for (int i = 0; i < TemplateBlocks.Num(); i++)
	{
		ABlockBase* Block = GetWorld()->SpawnActor<ABlockBase>(TemplateBlocks[i], SpawnInfo);
		Block->SetActorEnableCollision(false);
		Block->SetActorHiddenInGame(true);
		Block->SetActorTickEnabled(false);
		Blocks.Add(Block);
	}
	Blocks.Sort([](const ABlockBase& LB, const ABlockBase& RB) -> bool {
		return LB.HeightValue > RB.HeightValue;
	});
}
void AMapGenerator::GenerateMap()
{
	TArray<TArray<float>*>* NoiseMap = NoisePerl::GenerateNoiseMap(MapWidth, MapHeight, Seed, NoiseScale, Octaves, Persistance, Lacunarity);

	DrawNoiseMap(NoiseMap);
}

void AMapGenerator::DrawNoiseMap(TArray<TArray<float>*>* NoiseMap)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	for (int y = 0; y != NoiseMap->Num(); y++)
	{
		TArray<float>* ValuesX = (*NoiseMap)[y];
		for (int x = 0; x != ValuesX->Num(); x++)
		{		
			float CurrentHeight = (*ValuesX)[x];
		
			FVector Location((float)x*16.0f, (float)y * 16.0f, ((int)((CurrentHeight)*10.0f))*16.0f);
			for (int i = 0; i < Blocks.Num(); i++)
			{
				if (CurrentHeight <= Blocks[i]->HeightValue)
				{
					GetWorld()->SpawnActor<ABlockBase>(TemplateBlocks[i], Location, Rotation, SpawnInfo);
					break;
				}

			}
			
			
		}
	}
}