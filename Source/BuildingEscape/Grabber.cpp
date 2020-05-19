// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetInputBindings();
}

void UGrabber::SetInputBindings()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Can't find Input component in %s"), *GetOwner()->GetName());
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Can't find Physicshandle component in %s"), *GetOwner()->GetName());
}

void UGrabber::Grab()
{
	UPrimitiveComponent* ComponentToGrab = GetFirstPhysicsBodyInReach().GetComponent();

	// if we hit something, we attach the physics handle
	if (ComponentToGrab)
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayersReach());
}

void UGrabber::Release()
{
	if (PhysicsHandle->GrabbedComponent)
		PhysicsHandle->ReleaseComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update grabbed item's location
	if (PhysicsHandle->GrabbedComponent)
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, 
		GetPlayerWorldPosition(), 
		GetPlayersReach(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return Hit;
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	return PlayerViewLocation;
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	return PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
}