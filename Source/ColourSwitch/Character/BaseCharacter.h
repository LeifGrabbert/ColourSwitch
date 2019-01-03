// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMode/ColourEnum.h"
#include "BaseCharacter.generated.h"

class UMaterial;
class AGameMode_ColourSwitch;
class AWaypoint;

UCLASS()
class COLOURSWITCH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Switch the colour of the player
	*/
	UFUNCTION(BlueprintCallable)
	void SwitchColour();

	/**
	* Returns the current colour of the  player
	*/
	inline EColour GetColour() { return currentColour; }

	/**
	* Adds a waypoint of the current level the array
	* @param Point: The waypoint that will be added
	*/
	inline void AddWaypoint(AWaypoint* Point) { waypoints.Add(Point); }

private:
	// Instance of the current game mode
	AGameMode_ColourSwitch* gameMode;

	// Array with all waypoints
	UPROPERTY(VisibleAnywhere, Category = "Defaults")
		TArray<AWaypoint*> waypoints;

	// The current target waypoint
	FVector currentTargetWaypoint;
	// The index of the last waypoint 
	int lastIndex;
	// The direction of the next waypoint
	FVector direction;

	// Keeps track of the current colour of the character
	UPROPERTY(VisibleAnywhere, Category = "Defaults|Colour")
		EColour currentColour;
	
	// Materials to choose from
	UPROPERTY(EditAnywhere, Category = "Defaults|Colour", meta = (AllowPrivateAccess = "true"))
		TArray<UMaterial*> materials;

#pragma region Speed variables
	// Base movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement", meta = (AllowPrivateAccess = "true"))
	float baseSpeed;
	
	// Max allowed speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement", meta = (AllowPrivateAccess = "true"))
	float maxSpeed;

	// Multiplikate the acceleration depending on the current speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement", meta = (AllowPrivateAccess = "true"))
	float accelerationMultiplikator;

	// Speed gained per consecutive pickup
	UPROPERTY(EditAnywhere, Category = "Defaults|Movement", meta = (AllowPrivateAccess = "true"))
	float consecutiveSpeed;

	// Current speed
	UPROPERTY(VisibleAnywhere, Category = "Defaults|Movement")
	float currentSpeed;

	// Current speed
	UPROPERTY(VisibleAnywhere, Category = "Defaults|Movement")
	float additionalSpeed;
#pragma endregion

	//################################################################################################
	//################################################################################################

	// Movement function
	void Move();

	// Calculate the additional movement speed
	void CalcCurrentSpeed();

	// Searches for every waypoint in the level 
	void SearchWaypoints();

	// Switches the current target to a new one
	void SwitchTarget();
};
