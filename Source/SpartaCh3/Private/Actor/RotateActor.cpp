#include "Actor/RotateActor.h"
#include "Components/StaticMeshComponent.h"

ARotateActor::ARotateActor()
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

void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (StartLocation.IsZero())
		StartLocation = GetActorLocation();
	SetActorLocation(StartLocation);
}

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

