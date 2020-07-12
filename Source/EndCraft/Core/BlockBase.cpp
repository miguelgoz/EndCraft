// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"


// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(CollisionMesh);

	BaseMeshRear = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RearMesh"));
	BaseMeshRear->SetupAttachment(CollisionMesh);
	BaseMeshFront = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FrontMesh"));
	BaseMeshFront->SetupAttachment(CollisionMesh);
	BaseMeshLeft = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LeftMesh"));
	BaseMeshLeft->SetupAttachment(CollisionMesh);
	BaseMeshRight = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RightMesh"));
	BaseMeshRight->SetupAttachment(CollisionMesh);
	BaseMeshTop = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopMesh"));
	BaseMeshTop->SetupAttachment(CollisionMesh);
	BaseMeshBottom = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomMesh"));
	BaseMeshBottom->SetupAttachment(CollisionMesh);
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

