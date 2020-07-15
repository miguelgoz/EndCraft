// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "BlockBase.generated.h"


class UBoxComponent;
UCLASS()
class ENDCRAFT_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	

	USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshRear;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshFront;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshLeft;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshRight;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshTop;
	UPROPERTY(VisibleDefaultsOnly)
	UPaperSpriteComponent* BaseMeshBottom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MapGenerator")
	float HeightValue = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FString Name = "Without NAME!!";

	ABlockBase();
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

private:

	float Durability;
	float Weight;
	bool Gravity;
	bool AllowThrough;


	void SetupComponents();
	void SetupMeshes();

};
