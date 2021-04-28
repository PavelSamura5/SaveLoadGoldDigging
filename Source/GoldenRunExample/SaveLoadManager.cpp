// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadManager.h"

#include "GenerateMap.h"
#include "Kismet/GameplayStatics.h"

#include "GoldenRunExampleCharacter.h"

// Sets default values
ASaveLoadManager::ASaveLoadManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveLoadManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaveLoadManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FSaveInformation ASaveLoadManager::Save(ACharacter* Character)
{
	FSaveInformation Saved;
	
	if(Cast<AGoldenRunExampleCharacter>(Character))
	{
		AGoldenRunExampleCharacter* GetCharacter = Cast<AGoldenRunExampleCharacter>(Character);
		
		Saved.ActorLocation = GetCharacter->GetActorLocation();
		Saved.CurrentDig = GetCharacter->DigCount;
		Saved.CurrentGold = GetCharacter->GoldCount;
		Saved.GoldArrayTexture2D = GetCharacter->ImageArray;

		FSaveArrayElementInfo ArrayInfo;
		TArray<AActor*> AllActor;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerateMap::StaticClass(), AllActor);

		for (AActor* TActor: AllActor)
		{
			AGenerateMap* MyActor;
			
			if(Cast<AGenerateMap>(TActor))
			{
				MyActor = Cast<AGenerateMap>(TActor);
				ArrayInfo.ClassLocation = MyActor->GetActorLocation();
				ArrayInfo.ClassHole = MyActor->StaticClass();
				Saved.ArrayInfo.Add(ArrayInfo);
			}
		}
		return Saved;
	}
	else
		return Saved;
	
}

bool ASaveLoadManager::Load(ACharacter* Character, FSaveInformation Saved)
{
	if(Cast<AGoldenRunExampleCharacter>(Character))
	{
		AGoldenRunExampleCharacter* GetCharacter = Cast<AGoldenRunExampleCharacter>(Character);
		GetCharacter->DigCount = Saved.CurrentDig;
		GetCharacter->GoldCount = Saved.CurrentGold;
		GetCharacter->ImageArray = Saved.GoldArrayTexture2D;

		for (int IndexWeight = 0; IndexWeight < Saved.ArrayInfo.Num(); IndexWeight++)
		{
			AGenerateMap* SpawnedHoleActorRef = GetWorld()->SpawnActor<AGenerateMap>(Saved.ArrayInfo[IndexWeight].ClassLocation, FRotator::ZeroRotator);
			SpawnedHoleActorRef->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
		}

		GetCharacter->SetActorLocation(FVector(Saved.ActorLocation.X, Saved.ActorLocation.Y, Saved.ActorLocation.Z + 500.f));
		
		return true;
	}
	else
		return false;
}



