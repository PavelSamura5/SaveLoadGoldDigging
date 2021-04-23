// Fill out your copyright notice in the Description page of Project Settings.


#include "Gold.h"

// Sets default values
AGold::AGold()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gold = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldMesh"));
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    
	RootComponent = Scene;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("'/Engine/BasicShapes/Cone.Cone'"));
	UStaticMesh* Asset = StaticMeshAsset.Object;

	Gold->SetStaticMesh(Asset);
	Gold->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

