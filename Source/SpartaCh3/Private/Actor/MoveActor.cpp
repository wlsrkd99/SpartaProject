// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MoveActor.h"

// Sets default values
AMoveActor::AMoveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoveActor::BeginPlay()
{
	Super::BeginPlay();
	ResetActorPosition();
	if (MoveDirection.IsZero())
		MoveDirection = GetActorForwardVector();
}

void AMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);
	
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	if (DistanceMoved >= MaxRange)
	{
		FVector TrimmedDirection = MoveDirection.GetSafeNormal();
		SetActorLocation(StartLocation + (TrimmedDirection * MaxRange));
		MoveDirection = -MoveDirection;
	}
}



void AMoveActor::ResetActorPosition()
{
	SetActorLocation(StartLocation);
}