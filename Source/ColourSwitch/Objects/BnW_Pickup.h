// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BasePickup.h"
#include "GameMode/ColourEnum.h"
#include "BnW_Pickup.generated.h"

class UMaterial;
class AGameMode_ColourSwitch;
class ABaseCharacter;

UCLASS()
class COLOURSWITCH_API ABnW_Pickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	ABnW_Pickup();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Colour enum
	UPROPERTY(EditAnywhere, Category = "Defaults")
	EColour pickupColour;

	// Materials to choose from
	UPROPERTY(EditAnywhere, Category = "Defaults")
	TArray<UMaterial*> materials;

	// Overlap
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

private:
	// Instance of the current game mode
	AGameMode_ColourSwitch* gameMode;

	// Instance of the player character
	ABaseCharacter* playerCharacter;
};
