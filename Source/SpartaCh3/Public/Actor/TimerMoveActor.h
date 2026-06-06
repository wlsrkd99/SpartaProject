// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/MoveActor.h"
#include "TimerMoveActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPARTACH3_API ATimerMoveActor : public AMoveActor
{
	GENERATED_BODY()
	
public:
	ATimerMoveActor();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TogglePlatform();
	UFUNCTION()
	void MoveToRandomLocation();
private:
	FTimerHandle ToggleTimerHandle;
	FTimerHandle MovementTimerHandle;
	bool bIsPlatformActive = true;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties")
	bool bToggle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties")
	float TogglePeriod = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties")
	bool bMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor|Properties")
	float MovePeriod = 3.f;
};
