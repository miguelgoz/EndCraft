// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	BaseMeshRear = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMeshRear->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



