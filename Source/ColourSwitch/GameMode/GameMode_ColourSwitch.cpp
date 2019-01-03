// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_ColourSwitch.h"
#include "UObject/ConstructorHelpers.h"

AGameMode_ColourSwitch::AGameMode_ColourSwitch()
{
	consecutivePickups = 0;
	currentFuelCapacity = 0;
	maxFuelCapacity = 100;
	increaseCurrentFuel = 1;
	decreaseCurrentFuel = 3;
}

void AGameMode_ColourSwitch::BeginPlay()
{
	Super::BeginPlay();

}

void AGameMode_ColourSwitch::IncreaseCurrentFuelCapacity()
{
	if ((currentFuelCapacity + increaseCurrentFuel) > maxFuelCapacity)
		currentFuelCapacity = maxFuelCapacity;
	else
		currentFuelCapacity += increaseCurrentFuel;
}

void AGameMode_ColourSwitch::DecreaseCurrentFuelCapacity()
{
	if ((currentFuelCapacity - decreaseCurrentFuel) < 0)
		currentFuelCapacity = 0;
	else
		currentFuelCapacity -= decreaseCurrentFuel;
}