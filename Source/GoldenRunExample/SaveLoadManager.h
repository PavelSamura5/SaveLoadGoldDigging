// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SaveLoadManager.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FSaveArrayElementInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* ClassHole;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ClassLocation;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSaveInformation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ActorLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentDig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSaveArrayElementInfo> ArrayInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	UFUNCTION(BlueprintCallable)
	FSaveInformation Save(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	bool Load(ACharacter* Character, FSaveInformation Saved);
};
