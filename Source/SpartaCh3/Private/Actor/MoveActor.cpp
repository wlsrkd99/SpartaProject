#include "Actor/MoveActor.h"
#include "Components/StaticMeshComponent.h"

AMoveActor::AMoveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
	}
}

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
	if (DistanceMoved >= MoveRange)
	{
		FVector TrimmedDirection = MoveDirection.GetSafeNormal();
		SetActorLocation(StartLocation + (TrimmedDirection * MoveRange));
		MoveDirection = -MoveDirection;
	}
}



void AMoveActor::ResetActorPosition()
{
	SetActorLocation(StartLocation);
}