// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoldenRunExamplePlayerController.h"

#include <UIAutomationCore.h>

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GoldenRunExampleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AGoldenRunExamplePlayerController::AGoldenRunExamplePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AGoldenRunExamplePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	
	if(bPressed)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if(Cast<AGold>(Hit.GetActor()))
		{
			Gold = Cast<AGold>(Hit.GetActor());
			Gold->SetActorLocation(FVector(Hit.Location.X, Hit.Location.Y, Gold->GetActorLocation().Z));
		}
	}
}

void AGoldenRunExamplePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AGoldenRunExamplePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AGoldenRunExamplePlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("ActivateDig", IE_Pressed, this, &AGoldenRunExamplePlayerController::OnRightMouseButtonPressed);
	InputComponent->BindAction("ActivateDig", IE_Released, this, &AGoldenRunExamplePlayerController::OnRightMouseButtonReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGoldenRunExamplePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AGoldenRunExamplePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AGoldenRunExamplePlayerController::OnResetVR);
}

void AGoldenRunExamplePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGoldenRunExamplePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AGoldenRunExampleCharacter* MyPawn = Cast<AGoldenRunExampleCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AGoldenRunExamplePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AGoldenRunExamplePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AGoldenRunExamplePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AGoldenRunExamplePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AGoldenRunExamplePlayerController::OnRightMouseButtonPressed()
{
	FHitResult Hit;
	AGoldenRunExampleCharacter* myCharacter = Cast<AGoldenRunExampleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
 
	if (Hit.bBlockingHit){
		if (Hit.Actor != nullptr)
		{
			if(Cast<AGenerateMap>(Hit.GetActor()))
			{
				AGenerateMap* Selected = Cast<AGenerateMap>(Hit.GetActor());
				const bool ResDigging = Selected->Digging(Gold);
				myCharacter->DigCount = myCharacter->DigCount - 1;
					
				if(myCharacter->DigCount > 0 && ResDigging)
				{
					ResultDigging = Selected->bDroppedGold;
				}
				else if(!ResDigging)
				{
					Selected->Destroy();
				}
			}
			else if(Cast<AGold>(Hit.GetActor()))
			{
				bPressed = true;
			}
		}
	}  
}

void AGoldenRunExamplePlayerController::OnRightMouseButtonReleased()
{
	bPressed = false;
}


