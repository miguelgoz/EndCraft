// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

UCLASS()
class ENDCRAFT_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	


	AMapGenerator();
	virtual void Tick(float DeltaTime) override;

	void GenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int MapWidth;
	int MapHeight;
	float NoiseScale;
	

};
