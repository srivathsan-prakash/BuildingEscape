// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	void SetInputBindings();
	void FindPhysicsHandle();
	void Grab();
	void Release();
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetPlayersReach() const;
	FVector GetPlayerWorldPosition() const;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float Reach = 200.0f;
};
