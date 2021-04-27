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

SaveInformation ASaveLoadManager::Save(ACharacter* Character)
{
	SaveInformation Saved;
	
	if(Cast<AGoldenRunExampleCharacter>(Character))
	{
		AGoldenRunExampleCharacter* GetCharacter = Cast<AGoldenRunExampleCharacter>(Character);
		
		Saved.ActorLocation = GetCharacter->GetActorLocation();
		Saved.CurrentDig = GetCharacter->DigCount;
		Saved.CurrentGold = GetCharacter->GoldCount;
		Saved.GoldArrayTexture2D = GetCharacter->ImageArray;

		SaveArrayElementInfo ArrayInfo;
		TArray<AActor*> AllActor;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerateMap::StaticClass(), AllActor);

		for (AActor* TActor: AllActor)
		{
			AGenerateMap* MyActor = Cast<AGenerateMap>(Character);
			if(MyActor != nullptr)
			{
				ArrayInfo.ClassLocation = MyActor->GetActorLocation();
				ArrayInfo.ClassHole = MyActor->StaticClass();
				Saved.ArrayInfo.Add(ArrayInfo);
			}
		}	
	}
	return Saved;
}

bool ASaveLoadManager::Load(ACharacter* Character, SaveInformation Saved)
{
	if(Cast<AGoldenRunExampleCharacter>(Character))
	{
		AGoldenRunExampleCharacter* GetCharacter = Cast<AGoldenRunExampleCharacter>(Character);
		GetCharacter->DigCount = Saved.CurrentDig;
		GetCharacter->GoldCount = Saved.CurrentGold;
		GetCharacter->ImageArray = Saved.GoldArrayTexture2D;

		for (int IndexWeight = 0; IndexWeight < Saved.ArrayInfo.Num(); IndexWeight++)
			AGenerateMap* SpawnedHoleActorRef = GetWorld()->SpawnActor<AGenerateMap>(Saved.ArrayInfo[IndexWeight].ClassLocation, FRotator::ZeroRotator);

		return true;
	}
	else
		return false;
}



