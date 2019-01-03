// Fill out your copyright notice in the Description page of Project Settings.

#include "BnW_Pickup.h"
#include "GameMode/GameMode_ColourSwitch.h"
#include "Character/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ABnW_Pickup::ABnW_Pickup()
{
	 //Add the overlapp function to this class
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABnW_Pickup::BeginOverlap);

	// Set default values
	materials.Init(nullptr, 2);
	pickupColour = EColour::Black;
}

void ABnW_Pickup::BeginPlay()
{
	Super::BeginPlay();

	// Get the instance of the current game mode and character
	gameMode = static_cast<AGameMode_ColourSwitch*>(GetWorld()->GetAuthGameMode());
	playerCharacter = static_cast<ABaseCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Set colour acordingly to editor settings
	if (pickupColour == EColour::Black)
	{
		if (materials[0])
			GetMeshComponent()->SetMaterial(0, materials[0]);
	}
	else
	{
		if (materials[1])
			GetMeshComponent()->SetMaterial(0, materials[1]);
	}
}

void ABnW_Pickup::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		//UE_LOG(LogClass, Warning, TEXT("Overlapping Player"));

		// Interaction between player and pickup
		if (gameMode && playerCharacter)
		{
			// If its the same colour add to points, else subtract
			if (playerCharacter->GetColour() == pickupColour)
			{
				gameMode->IncreaseConsecutivePickups();
				gameMode->IncreaseCurrentFuelCapacity();
				Destroy();
			}
			else
			{
				gameMode->ResetConsecutivePickups();
				gameMode->DecreaseCurrentFuelCapacity();
				Destroy();
			}
		}
	}
}
