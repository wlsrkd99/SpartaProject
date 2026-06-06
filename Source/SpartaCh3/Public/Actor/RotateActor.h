// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPARTACH3_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor|Properties")
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor|Properties")
	FVector RotationDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties", meta = (ClampMin="0.0"))
	float RotationSpeed;
	
};
