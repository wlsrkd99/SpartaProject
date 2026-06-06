// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|Property")
	TSubclassOf<AActor> PlatformClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|Property", meta = (MakeEditWidget = true))
	FVector SpawnLocation;

	FPuzzleSpawnInfo() : PlatformClass(nullptr), SpawnLocation(FVector::ZeroVector) {}
	FPuzzleSpawnInfo(TSubclassOf<AActor> InClass, FVector InLocation) : PlatformClass(InClass), SpawnLocation(InLocation) {}
};

UCLASS()
class SPARTACH3_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleManager();

protected:
	virtual void BeginPlay() override;
	void SpawnPlatform();
	
private:
	FVector GetRandomDirection();
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|Property")
	TArray<FPuzzleSpawnInfo> SpawnInfos;
	
};