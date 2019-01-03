// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameMode/GameMode_ColourSwitch.h"
#include "Waypoint.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EngineUtils.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values
	Tags.Add("Player");
	currentColour = EColour::Black;
	materials.Init(nullptr, 2);

	baseSpeed = 300.0f;
	currentSpeed = baseSpeed;
	maxSpeed = 3000.0f;
	additionalSpeed = 0.0f;
	consecutiveSpeed = 500.0f;
	lastIndex = 0;
	direction = FVector(0.0f, 0.0f, 0.0f);
	accelerationMultiplikator = 7.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set the right colour at the beginning
	if (materials[0])
		GetMesh()->SetMaterial(0, materials[0]);

	// Get the current game mode
	gameMode = static_cast<AGameMode_ColourSwitch*>(GetWorld()->GetAuthGameMode());

	// Search for all the waypoints in the level
	SearchWaypoints();

	// Set the first waypoint
	if (waypoints.Num() != 0 && waypoints[0] != nullptr)
	{
		currentTargetWaypoint = waypoints[0]->GetActorLocation();
		direction = currentTargetWaypoint - GetActorLocation();
	}
		
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalcCurrentSpeed();
	Move();
}

void ABaseCharacter::Move()
{
	// Get the distance to the current waypoint
	float distance = FVector::Dist(FVector(currentTargetWaypoint.X, 0.0f, currentTargetWaypoint.Z), FVector(GetActorLocation().X, 0.0f, GetActorLocation().Z));

	// Switch the waypoints if you are close enough to one
	if (distance < 100.0f)
	{
		// Switch Target
		SwitchTarget();
		direction = currentTargetWaypoint - GetActorLocation();
	}

	// Actual movement
	AddMovementInput(direction.GetSafeNormal(), currentSpeed);
}

void ABaseCharacter::SwitchTarget()
{
	if (waypoints.Num() != 0 && lastIndex + 1 < waypoints.Num())
		currentTargetWaypoint = waypoints[lastIndex++]->GetActorLocation();
	else
		currentTargetWaypoint = GetActorLocation() + FVector(10000.0f, 0.0f, 0.0f);
}

void ABaseCharacter::CalcCurrentSpeed()
{
	// Calculate the additional speed
	additionalSpeed = consecutiveSpeed * gameMode->GetConsecutivePickups();

	// Calculate the current speed
	GetCharacterMovement()->MaxFlySpeed = baseSpeed + additionalSpeed;
	GetCharacterMovement()->MaxAcceleration = (baseSpeed + additionalSpeed) * accelerationMultiplikator;
}

void ABaseCharacter::SwitchColour()
{
	// Switch to the right material accordingly to the enum
	if (currentColour == EColour::Black)
	{
		if (materials[1])
		{
			GetMesh()->SetMaterial(0, materials[1]);
			currentColour = EColour::White;
		}
	}
	else
	{
		if (materials[0])
		{
			GetMesh()->SetMaterial(0, materials[0]);
			currentColour = EColour::Black;
		}
	}
}

void ABaseCharacter::SearchWaypoints()
{
	for (TActorIterator<AWaypoint> i(GetWorld()); i; ++i)
	{
		waypoints.Add(*i);
	}
}
