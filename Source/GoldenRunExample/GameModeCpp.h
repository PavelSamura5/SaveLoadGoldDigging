// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveLoadManager.h"
#include "Manager.h"

#include "GameModeCpp.generated.h"

/**
 * 
 */

UCLASS()
class GOLDENRUNEXAMPLE_API AGameModeCpp : public AGameModeBase
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	AGameModeCpp();

	// Called every frame
	class ASaveLoadManager* SaveLoadManagerReference;

	void DefaultStartGame();

	void LoadStartGame(TArray<SaveInformation> ArrayInfo);

};
