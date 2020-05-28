// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle +=  InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the door component, but no pressure plate set!"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > OpenDoorMass)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator DoorRotation{ GetOwner()->GetActorRotation() };
	//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), DoorRotation.Yaw);

	//CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 0.5f);
	//CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 90);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);

	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator DoorRotation{ GetOwner()->GetActorRotation() };
	//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), DoorRotation.Yaw);

	//CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 0.5f);
	//CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 90);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);

	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass{ 0.f };

	TArray<AActor *> OverlappingActors{};

	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (AActor *Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

