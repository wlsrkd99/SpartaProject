// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RotateActor.h"

// Sets default values
ARotateActor::ARotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(StartLocation);
}

// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		FRotator DeltaRotation;
		FVector SafeRotation = RotationDirection.GetClampedToMaxSize(1.0f);
		DeltaRotation.Pitch = SafeRotation.Y * RotationSpeed * DeltaTime;
		DeltaRotation.Yaw   = SafeRotation.Z * RotationSpeed * DeltaTime;
		DeltaRotation.Roll  = SafeRotation.X * RotationSpeed * DeltaTime;
		AddActorLocalRotation(DeltaRotation);
	}
}

