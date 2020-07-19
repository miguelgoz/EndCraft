// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include "Noise/NoisePerl.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	GenerateChunk();
	InitializeBlocks();

}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsGenerated)
	{
		DrawNextBlock();
	}
	else 
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}
void AChunk::InitializeBlocks()
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
void AChunk::GenerateChunk()
{
	NoiseMap = NoisePerl::GenerateNoiseMap(ChunkSize, Seed, NoiseScale, Octaves, Persistance, Lacunarity, X0, Y0);

}

void AChunk::DrawNextBlock()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	if (y == NoiseMap->Num()) 
	{
		IsGenerated = true;
		return;
	}
	TArray<float>* ValuesX = (*NoiseMap)[y];
	if (x == ValuesX->Num()) 
	{
		y++;
		x = 0;
		return;
	}
	else 
	{
		float CurrentHeight = (*ValuesX)[x];

		FVector Location((float)x * 16.0f, (float)y * 16.0f, ((int)((CurrentHeight) * 10.0f)) * 16.0f);

		for (int i = 0; i < Blocks.Num(); i++)
		{
			if (CurrentHeight <= Blocks[i]->HeightValue)
			{
				GetWorld()->SpawnActor<ABlockBase>(TemplateBlocks[i], Location, Rotation, SpawnInfo);
				break;
			}

		}
		x++;
	}
	
}