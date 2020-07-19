// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blocks/BlockBase.h"
#include "Chunk.generated.h"

class ABlockBase;
UCLASS()
class ENDCRAFT_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	int ChunkSize = 16;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	int Seed = 70000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	int Octaves = 4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	float NoiseScale = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	float Persistance = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	float Lacunarity = 0.05f;

	int X0 = 0;
	int Y0 = 0;

	bool IsGenerated = false;
	int y = 0;
	int x = 0;
	TArray<ABlockBase*> BlocksGenerated;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocks")
	TArray<TSubclassOf<ABlockBase>> TemplateBlocks;
	TArray<ABlockBase*> Blocks;
	TArray<TArray<float>*>* NoiseMap;


	AChunk();
	virtual void Tick(float DeltaTime) override;

	void GenerateChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:





	void DrawNextBlock();
	void DrawDeepBlocks(TSubclassOf<ABlockBase> NewBlock, int z, int Deep);
	void InitializeBlocks();

};
