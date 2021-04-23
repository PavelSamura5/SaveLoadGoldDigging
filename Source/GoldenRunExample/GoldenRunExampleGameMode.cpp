// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoldenRunExampleGameMode.h"
#include "GoldenRunExamplePlayerController.h"
#include "GoldenRunExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGoldenRunExampleGameMode::AGoldenRunExampleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGoldenRunExamplePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}