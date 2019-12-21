// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "Engine/World.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Survivor/Public/InteractionInterface.h"

// Sets default values
APlayerBase::APlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerBase::StartSpinting()
{
	if (CanSprint())
	{
		bIsSprinting = true;
		if (Cast<UCharacterMovementComponent>(GetMovementComponent()) != nullptr) 
		{
			Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = SprintSpeed;
		}
	}
}

void APlayerBase::StopSpinting()
{
	bIsSprinting = false;
	if (Cast<UCharacterMovementComponent>(GetMovementComponent()) != nullptr)
	{
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

void APlayerBase::StartCrouch()
{
	if (CanCrouch())
	{
		StopSpinting();
		Crouch();
	}
}

void APlayerBase::StopCrouch()
{
	UnCrouch();
}


bool APlayerBase::CanSprint_Implementation()
{
	if (!bIsCrouched) { return true; }
	return false;
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent != nullptr)
	{
		InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &APlayerBase::StartCrouch);

		InputComponent->BindAction("Crouch", EInputEvent::IE_Released, this, &APlayerBase::StopCrouch);

		InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerBase::StartSpinting);

		InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerBase::StopSpinting);
	}
}

