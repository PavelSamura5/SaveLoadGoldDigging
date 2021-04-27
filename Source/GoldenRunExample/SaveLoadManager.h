// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SaveLoadManager.generated.h"

struct SaveArrayElementInfo
{
	UClass* ClassHole;
	FVector ClassLocation;
};

struct SaveInformation
{
	FVector ActorLocation;
	int32 CurrentDig;
	int32 CurrentGold;
	TArray<SaveArrayElementInfo> ArrayInfo;
	TArray<UTexture2D*> GoldArrayTexture2D;
};

UCLASS()
class GOLDENRUNEXAMPLE_API ASaveLoadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveLoadManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	SaveInformation Save(ACharacter* Character);
	bool Load(ACharacter* Character, SaveInformation Saved);
};
