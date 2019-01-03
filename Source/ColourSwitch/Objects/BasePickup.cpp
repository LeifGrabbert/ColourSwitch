// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create Capsule Component
	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = capsuleComponent;
	//capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::BeginOverlap);

	// Create Static Mesh Component
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

//void ABasePickup::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult & SweepResult)
//{
//}

