// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class COLOURSWITCH_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
	/** Capsule Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* capsuleComponent;
	/** Static Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* meshComponent;
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Getter
	UCapsuleComponent* GetCapsuleComponent() const { return capsuleComponent; }
	UStaticMeshComponent* GetMeshComponent() const { return meshComponent; }

public:
	//// Overlap
	//UFUNCTION()
	//	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
};
