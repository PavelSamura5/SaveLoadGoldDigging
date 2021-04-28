// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateMap.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Gold.h"

// Sets default values
AGenerateMap::AGenerateMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Hole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoleMesh"));
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    
    RootComponent = Scene;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	UStaticMesh* Asset = StaticMeshAsset.Object;

	Hole->SetStaticMesh(Asset);
    Hole->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGenerateMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerateMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGenerateMap::Digging(AGold*& ReturnActor)
{
	DigHeight = DigHeight - 1;

	if (FMath::RandRange(0, 1000) > 500)
	{
		AGold* SpawnedHoleActorRef = GetWorld()->SpawnActor<AGold>(GetActorLocation(), GetActorRotation());
		ReturnActor = SpawnedHoleActorRef;
		bDroppedGold = true;
	}

	if(DigHeight <= 0)
		return false;
	else
		return true;
}



