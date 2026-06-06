// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPARTACH3_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveActor();
	
	UFUNCTION(BlueprintCallable, Category = "Actor|Actions")
	void ResetActorPosition();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor|Properties")
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor|Properties")
	FVector MoveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties", meta = (ClampMin="0.0"))
	float MoveRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties", meta = (ClampMin="0.0"))
	float MoveSpeed;
};
