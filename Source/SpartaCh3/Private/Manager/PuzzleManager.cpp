#include "Manager/PuzzleManager.h"
#include "Engine/World.h"
#include "Actor/MoveActor.h"
#include "Actor/RotateActor.h"
#include "Actor/TimerMoveActor.h"

APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpawnInfos.Add(FPuzzleSpawnInfo(AMoveActor::StaticClass(), FVector(100.f, 0.f, 0.f)));
	SpawnInfos.Add(FPuzzleSpawnInfo(ARotateActor::StaticClass(), FVector(300.f, 200.f, 50.f)));
	SpawnInfos.Add(FPuzzleSpawnInfo(ATimerMoveActor::StaticClass(), FVector(500.f, -100.f, 100.f)));
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnPlatform();
}

void APuzzleManager::SpawnPlatform()
{
	UWorld* World = GetWorld();
	if (!World) return;

	const FVector ManagerLocation = GetActorLocation();

	for (const FPuzzleSpawnInfo& SpawnInfo : SpawnInfos)
	{
		if (SpawnInfo.PlatformClass)
		{
			const FVector SpawnLocation = ManagerLocation + SpawnInfo.SpawnLocation;
			const FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);
			AActor* SpawnedActor = World->SpawnActorDeferred<AActor>(SpawnInfo.PlatformClass, SpawnTransform, this);

 			if (SpawnedActor)
 			{
 				if (ATimerMoveActor* TimerMoveActor = Cast<ATimerMoveActor>(SpawnedActor))
 				{
 					TimerMoveActor->StartLocation = SpawnLocation;
 					if (FMath::RandBool())
 					{
 						TimerMoveActor->bToggle = true;
 						TimerMoveActor->bMove = false;
 						TimerMoveActor->TogglePeriod = FMath::FRandRange(1.0f, 5.0f);
 					}
 					else
 					{
 						TimerMoveActor->bToggle = false;
 						TimerMoveActor->bMove = true;
 						TimerMoveActor->MovePeriod = FMath::FRandRange(1.0f, 4.0f);
 						TimerMoveActor->MoveSpeed = FMath::FRandRange(100.f, 400.f);
 						TimerMoveActor->MoveRange = FMath::FRandRange(150.f, 800.f);
 						TimerMoveActor->MoveDirection = GetRandomDirection();
 					}
 				}
 				else if (AMoveActor* MoveActor = Cast<AMoveActor>(SpawnedActor))
 				{
 					MoveActor->MoveSpeed = FMath::FRandRange(100.f, 500.f);
 					MoveActor->MoveRange = FMath::FRandRange(200.f, 1000.f);
 					MoveActor->StartLocation = SpawnLocation;
 					MoveActor->MoveDirection = GetRandomDirection();
 				}
 				else if (ARotateActor* RotateActor = Cast<ARotateActor>(SpawnedActor))
 				{
 					RotateActor->RotationSpeed = FMath::FRandRange(45.f, 180.f);
 					RotateActor->StartLocation = SpawnLocation;
 					RotateActor->RotationDirection = GetRandomDirection();
 				}
				SpawnedActor->FinishSpawning(SpawnTransform);
 			}
		}
	}
}

FVector APuzzleManager::GetRandomDirection()
{
	FVector Direction = FVector::ZeroVector;
	TArray<int32> Axes = {0, 1, 2};

	for (int32 i = 0; i < Axes.Num(); ++i)
	{
		int32 SwapIndex = FMath::RandRange(i, Axes.Num() - 1);
		Axes.Swap(i, SwapIndex);
	}

	int32 ActiveAxesCount = FMath::RandRange(1, 3);

	for (int32 i = 0; i < ActiveAxesCount; ++i)
	{
		int32 CurrentAxis = Axes[i];
		float Sign = FMath::RandBool() ? 1.0f : -1.0f;

		if (CurrentAxis == 0) Direction.X = Sign;
		else if (CurrentAxis == 1) Direction.Y = Sign;
		else Direction.Z = Sign;
	}

	if (!Direction.IsNearlyZero())
	{
		Direction.Normalize();
	}
	return Direction;
}