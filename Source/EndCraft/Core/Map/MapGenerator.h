// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Blocks/BlockBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MapGenerator.generated.h"

class ABlockBase;
UCLASS()
class ENDCRAFT_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocks")
	TArray<TSubclassOf<ABlockBase>> TemplateBlocks;
	TArray<ABlockBase*> Blocks;
	
	AMapGenerator();
	virtual void Tick(float DeltaTime) override;

	void GenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	
	int MapWidth = 32;
	int MapHeight = 32;
	int Seed = 70000;
	int Octaves = 4;
	float NoiseScale = 10.0f;
	float Persistance = 0.005f;
	float Lacunarity = 1.0f;
	
	
	void DrawNoiseMap(TArray<TArray<float>*>* NoiseMap);
	void InitializeBlocks();
};
