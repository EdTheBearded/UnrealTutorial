// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"

// Bottom include
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;

private:

	float InitialYaw{};
	float CurrentYaw{};

	UPROPERTY(EditAnywhere)
	float OpenAngle{90.f};

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay{0.15f};

	float DoorLastOpened{};

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed{2};

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed{2};

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate{ nullptr };

	UPROPERTY(EditAnywhere)
	float OpenDoorMass{ 60.f };
};
