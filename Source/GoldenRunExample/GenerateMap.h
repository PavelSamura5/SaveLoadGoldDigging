// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gold.h"
#include "GenerateMap.generated.h"

UCLASS()
class GOLDENRUNEXAMPLE_API AGenerateMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Hole;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Scene;
	
	float DigHeight = 3;

public:	
	// Called every frame

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bDroppedGold = false;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool Digging(AGold*& ReturnActor);

};
