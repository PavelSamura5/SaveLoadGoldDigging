// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

// Sets default values
AManager::AManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AGenerateMap*> AManager::GeneratingMap(const int32 Size, const FSpawnTransform Transform)
{
	FSpawnTransform CurrentTransform = Transform;
	TArray<AGenerateMap*> ActorsArray = {};
	
	for (int IndexWeight = 0; IndexWeight < Size; IndexWeight++)
	{
		for (int IndexHeight = 0; IndexHeight < Size; IndexHeight++)
		{
			AGenerateMap* SpawnedHoleActorRef = GetWorld()->SpawnActor<AGenerateMap>(CurrentTransform.Location, CurrentTransform.Rotation);
			ActorsArray.Add(SpawnedHoleActorRef);
			
			CurrentTransform.Location.Y += 100;
		}
		CurrentTransform.Location.X += 100;
		CurrentTransform.Location.Y = Transform.Location.Y;
	}
	return ActorsArray;
}

