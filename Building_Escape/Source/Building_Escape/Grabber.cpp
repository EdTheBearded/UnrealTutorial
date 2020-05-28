// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult{ GetFirstPhysicsBodyInReach() };
	UPrimitiveComponent *ComponentToGrab{ HitResult.GetComponent() };

	if (HitResult.GetActor() && PhysicsHandle)
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayerReach());
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->ReleaseComponent();
	}
}

// Checking for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Could not get PhysicsHandleComponent reference!"), *GetOwner()->GetName());
	}
}

// Checking for Input Component, and setup Grab action
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Could not get InputComponent reference!"), *GetOwner()->GetName());
	}
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Raycast to find the first Actor with PhysicsBody within reach
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit{};
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}
// Calculate where the grabbing reach line ends and return its point
FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerViewPointLocation{};
	FRotator PlayerViewPointRotation{};

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return  PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
}

// Retrieves players viewpoint position
FVector UGrabber::GetPlayerWorldPos() const
{
	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}

