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
	ABlockBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAcces = "true"))
	UBoxComponent* CollisionMesh = nullptr;
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

protected:
	virtual void BeginPlay() override;

private:

	FString Name;
	float Durability;
	float Weight;
	bool Gravity;
	bool AllowThrough;

	


};
