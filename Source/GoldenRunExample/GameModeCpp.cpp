// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeCpp.h"
#include "GoldenRunExamplePlayerController.h"
#include "GoldenRunExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameModeCpp::AGameModeCpp()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGoldenRunExamplePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GoldenRunExample/Characters/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	static ConstructorHelpers::FObjectFinder<UClass> HUDFinder(TEXT("Blueprint'/Game/GoldenRunExample/HUD/BP_HUDGame.BP_HUDGame_C'"));
	HUDClass = (UClass *) HUDFinder.Object;
}

void AGameModeCpp::DefaultStartGame()
{
	AManager* Manager = GetWorld()->SpawnActor<AManager>(FVector::ZeroVector, FRotator::ZeroRotator);

	FSpawnTransform Transform;
	Transform.Rotation = FRotator::ZeroRotator;
	Transform.Location = FVector(100, -1000, 200);

	TArray<AGenerateMap*> Mapping = Manager->GeneratingMap(10, Transform);

	for (AGenerateMap* Actor : Mapping)
		Actor->SetActorScale3D(FVector(0.5, 0.5, 0.5));

	SaveLoadManagerReference = GetWorld()->SpawnActor<ASaveLoadManager>(FVector::ZeroVector, FRotator::ZeroRotator);
}

void AGameModeCpp::LoadStartGame(TArray<FSaveInformation> ArrayInfo)
{
	for (int Index = 0; Index < ArrayInfo.Num(); Index++)
	{
		AGenerateMap* CreateActor = GetWorld()->SpawnActor<AGenerateMap>(ArrayInfo[Index].ArrayInfo[Index].ClassLocation, FRotator::ZeroRotator);
		CreateActor->SetActorScale3D(FVector(0.5,0.5,0.5));
	}

	SaveLoadManagerReference = GetWorld()->SpawnActor<ASaveLoadManager>(FVector::ZeroVector, FRotator::ZeroRotator);
}

