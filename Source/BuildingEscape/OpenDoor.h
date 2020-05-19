// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOpenDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveDoor(float DeltaTime, float Target, float SpeedMultiplier);
	int32 TotalMassOfActors() const;

protected:
	virtual void BeginPlay() override;

private:
	float DoorLastOpened = 0.0f;
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float FinalYaw = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	int32 RequiredMass = 50.0f;

	UPROPERTY(EditAnywhere)
	float OpenSpeedMultiplier = 1.0f;

	UPROPERTY(EditAnywhere)
	float CloseSpeedMultiplier = 3.0f;
};
