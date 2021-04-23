// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateMap.h"
#include "Manager.generated.h"

USTRUCT(BlueprintType)
struct FSpawnTransform
{
	GENERATED_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
};

UCLASS()
class GOLDENRUNEXAMPLE_API AManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	TArray<AGenerateMap*> GeneratingMap(const int32 Size, const FSpawnTransform Transform);
};
