// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameMode_ColourSwitch.generated.h"

class AWaypoint;

UCLASS()
class COLOURSWITCH_API AGameMode_ColourSwitch : public AGameMode
{
	GENERATED_BODY()

public:
	// Basic Constructor
	AGameMode_ColourSwitch();

	// Getter
	
	// Return the consecutive pickup amount
	UFUNCTION(BlueprintCallable)
	inline int GetConsecutivePickups() const { return consecutivePickups; }
	
	// Return the current fuel capacity 
	UFUNCTION(BlueprintCallable)
	inline int GetCurrentFuelCapacity() const { return currentFuelCapacity; }
	
	// Return the max fuel capacity
	UFUNCTION(BlueprintCallable)
	inline int GetMaxFuelCapacity() const { return maxFuelCapacity; }

	// Setter
	
	/** 
	* Increases the consecutive pickup counter by one 
	*/
	inline void IncreaseConsecutivePickups() { consecutivePickups++; }
	
	/**
	* Resets the consecutive counter to 0
	*/
	inline void ResetConsecutivePickups() { consecutivePickups = 0; }

	/**
	* Increases the current fuel capacity by one
	*/
	void IncreaseCurrentFuelCapacity();

	/**
	* Decreases the current fuel capacity
	*/
	void DecreaseCurrentFuelCapacity();

private:
	void BeginPlay() override;

	// The counter that tracks how many times the player picked up the right colour in a row
	UPROPERTY(VisibleAnywhere, Category = "Defaults")
	int consecutivePickups;

	// Tracks the current fuel capacity
	UPROPERTY(VisibleAnywhere, Category = "Defaults")
	int currentFuelCapacity;

	// Tracks the max fuel capacity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int maxFuelCapacity;

	// Determines how much a single pickup will increase the fuel capacity by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int increaseCurrentFuel;

	// Determines how much a wrong pickup will decrease the fuel capacity by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	int decreaseCurrentFuel;
};
