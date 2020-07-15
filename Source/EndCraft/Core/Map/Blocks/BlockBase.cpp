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

	SetupComponents();
	SetupMeshes();


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

void ABlockBase::SetupComponents()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	BaseMeshRear = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RearMesh"));
	BaseMeshRear->SetupAttachment(RootComponent);
	BaseMeshFront = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FrontMesh"));
	BaseMeshFront->SetupAttachment(RootComponent);
	BaseMeshLeft = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LeftMesh"));
	BaseMeshLeft->SetupAttachment(RootComponent);
	BaseMeshRight = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RightMesh"));
	BaseMeshRight->SetupAttachment(RootComponent);
	BaseMeshTop = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopMesh"));
	BaseMeshTop->SetupAttachment(RootComponent);
	BaseMeshBottom = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomMesh"));
	BaseMeshBottom->SetupAttachment(RootComponent);
}

void ABlockBase::SetupMeshes()
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> DefaultSprite(TEXT("/Game/Sprites/SPR_Default.SPR_Default"));
	BaseMeshRear->SetSprite(DefaultSprite.Object);
	BaseMeshRear->SetRelativeLocation(FVector(0.0f, -8.0f, 0.0f));

	BaseMeshFront->SetSprite(DefaultSprite.Object);
	BaseMeshFront->SetRelativeLocation(FVector(0.0f, 8.0f, 0.0f));

	BaseMeshLeft->SetSprite(DefaultSprite.Object);
	BaseMeshLeft->SetRelativeLocation(FVector(-8.0f, 0.0f, 0.0f));
	BaseMeshLeft->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f,0.0f,90.0f)));

	BaseMeshRight->SetSprite(DefaultSprite.Object);
	BaseMeshRight->SetRelativeLocation(FVector(8.0f, 0.0f, 0.0f));
	BaseMeshRight->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, -90.0f)));

	BaseMeshTop->SetSprite(DefaultSprite.Object);
	BaseMeshTop->SetRelativeLocation(FVector(0.0f, 0.0f, 8.0f));
	BaseMeshTop->SetRelativeRotation(FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 0.0f)));

	BaseMeshBottom->SetSprite(DefaultSprite.Object);
	BaseMeshBottom->SetRelativeLocation(FVector(0.0f, 0.0f, -8.0f));
	BaseMeshBottom->SetRelativeRotation(FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 0.0f)));

	BaseMeshRear->SetCastShadow(true);
	BaseMeshFront->SetCastShadow(true);
	BaseMeshLeft->SetCastShadow(true);
	BaseMeshRight->SetCastShadow(true);
	BaseMeshTop->SetCastShadow(true);
	BaseMeshBottom->SetCastShadow(true);
}

