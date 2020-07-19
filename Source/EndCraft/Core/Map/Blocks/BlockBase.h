// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "BlockBase.generated.h"



UCLASS()
class ENDCRAFT_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* BaseMeshRear;
	


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MapGenerator")
	float HeightValue = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MapGenerator")
	int DeepBlocks = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FString Name = "Without NAME!!";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MapGenerator")
	TSubclassOf<ABlockBase> DeepBlock;

	ABlockBase();
	virtual void Tick(float DeltaTime) override;



protected:
	virtual void BeginPlay() override;

private:

	float Durability;
	float Weight;
	bool Gravity;
	bool AllowThrough;

};
