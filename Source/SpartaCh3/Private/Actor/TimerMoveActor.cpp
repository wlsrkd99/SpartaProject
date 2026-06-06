#include "Actor/TimerMoveActor.h"

ATimerMoveActor::ATimerMoveActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATimerMoveActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (bToggle)
	{
		GetWorld()->GetTimerManager().SetTimer(
			ToggleTimerHandle, 
			this, 
			&ATimerMoveActor::TogglePlatform, 
			TogglePeriod, 
			true
		);
	}
	
	if (bMove)
	{
		GetWorld()->GetTimerManager().SetTimer(
			MovementTimerHandle, 
			this, 
			&ATimerMoveActor::MoveToRandomLocation, 
			MovePeriod, 
			true
		);
	}
}

void ATimerMoveActor::TogglePlatform()
{
	bIsPlatformActive = !bIsPlatformActive;
	SetActorHiddenInGame(!bIsPlatformActive);
	SetActorEnableCollision(bIsPlatformActive);
}

void ATimerMoveActor::MoveToRandomLocation()
{
	float RandX = FMath::RandRange(-MoveRange, MoveRange);
	float RandY = FMath::RandRange(-MoveRange, MoveRange);
	float RandZ = FMath::RandRange(-MoveRange, MoveRange);
    
	FVector NewTargetLocation = StartLocation + FVector(RandX, RandY, RandZ);
	SetActorLocation(NewTargetLocation);
}

