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
		for (int i = 0; i < 50 && !IsGenerated; i++)
		{
			DrawNextBlock();
		}
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

		float z = ((int)((CurrentHeight) * 10.0f)) * 16.0f;

		FVector Location((float)x * 16.0f, (float)y * 16.0f, z);

		for (int i = 0; i < Blocks.Num(); i++)
		{
			if (CurrentHeight <= Blocks[i]->HeightValue)
			{
				ABlockBase* NewBlock = GetWorld()->SpawnActor<ABlockBase>(TemplateBlocks[i], Location, Rotation, SpawnInfo);
				BlocksGenerated.Add(NewBlock);
				DrawDeepBlocks(NewBlock->DeepBlock,z, NewBlock->DeepBlocks);
				break;
			}

		}
		x++;
	}
	
}
void AChunk::DrawDeepBlocks(TSubclassOf<ABlockBase> NewBlock, int z, int Deep)
{
	if (!NewBlock)
	{
		return;
	}
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	for (int i = 1; i <= Deep; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Deep = %f"), z);
		z = z - 16.0f;
		FVector Location((float)x * 16.0f, (float)y * 16.0f, z);
		ABlockBase* NewBlockDeep = GetWorld()->SpawnActor<ABlockBase>(NewBlock, Location, Rotation, SpawnInfo);
		BlocksGenerated.Add(NewBlockDeep);
	}
}