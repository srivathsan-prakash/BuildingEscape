// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "GameFrameWork/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Error, TEXT("In Constructor"));
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("In BeginPlay"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));

	//FString log = TEXT("Hello");
	//FString* logPtr = &log;

	//int32 l1 = (*logPtr).Len();
	//int32 l2 = logPtr->Len();

	//UE_LOG(LogTemp, Warning, TEXT("%s, %i, %i"), *log, l1, l2);

	FString name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *name);

	FString location = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *location);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

