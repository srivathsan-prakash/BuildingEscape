// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFrameWork/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > RequiredMass)
	{
		OnOpen.Broadcast();

		if (!AudioComponent) { UE_LOG(LogTemp, Warning, TEXT("Audio Component missing in %s"), *GetOwner()->GetName()); return; }

		if (!bOpenSoundPlayed)
		{
			AudioComponent->Play();
			bOpenSoundPlayed = true;
			bCloseSoundPlayed = false;
		}
	}
	else
	{
		OnClose.Broadcast();

		if (!AudioComponent) { UE_LOG(LogTemp, Warning, TEXT("Audio Component missing in %s"), *GetOwner()->GetName()); return; }

		if (!bCloseSoundPlayed)
		{
			AudioComponent->Play();
			bCloseSoundPlayed = true;
			bOpenSoundPlayed = false;
		}
	}
}

int32 UOpenDoor::TotalMassOfActors() const
{
	int32 TotalMass = 0.0f;

	if (!PressurePlate) { UE_LOG(LogTemp, Warning, TEXT("PressurePlate error in TotalMassOfActors")); return TotalMass; }

	//find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//add up their masses
	for (AActor* actor : OverlappingActors)
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

	return TotalMass;
}

