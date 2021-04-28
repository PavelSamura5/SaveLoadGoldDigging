// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveLoadManager.h"
#include "FileLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENRUNEXAMPLE_API UFileLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SaveFromFile(FSaveInformation Info);

	UFUNCTION(BlueprintCallable)
	static FSaveInformation LoadFromFile();
};
