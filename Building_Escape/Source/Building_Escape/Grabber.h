// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Bottom include
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach{ 150.f };

	UPhysicsHandleComponent *PhysicsHandle{ nullptr };
	UInputComponent *InputComponent{ nullptr };

	void Grab();
	void Release();

	// Checking for Physics Handle Component
	void FindPhysicsHandle();

	// Checking for Input Component, and setup Grab action
	void SetupInputComponent();

	/**
	 * Raycast to find the first Actor with PhysicsBody within reach
	 * @return Return FHitResult with found Actor
	 */
	FHitResult GetFirstPhysicsBodyInReach() const;

	/**
	 * Calculate where the grabbing reach line ends and return its point
	 * @return Return FVector with coordinates of grab reach end point
	 */
	FVector GetPlayerReach() const;

	/**
	 * Retrieves players viewpoint position
	 * @return returns FVector with player's viewpoint position
	 */
	FVector GetPlayerWorldPos() const;
};
