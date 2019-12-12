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
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerBase::OnUse()
{
	FHitResult hit;
	if (GetCamera() != nullptr)
	{
	
		GetWorld()->LineTraceSingleByChannel(hit,GetCameraWorldLocation(), GetCameraWorldLocation() + GetCamera()->GetForwardVector() * 500, ECollisionChannel::ECC_Camera);
		if (hit.bBlockingHit)
		{
			if (hit.GetActor()->Implements<UInteractionInterface>() || (Cast<IInteractionInterface>(hit.GetActor()) != nullptr))
			{
				
				IInteractionInterface::Execute_OnInteraction(hit.GetActor(), this, hit.GetComponent());
			}
		}
	}
	else
	{
		GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(),GetActorLocation() + this->RootComponent->GetForwardVector()* 300, ECollisionChannel::ECC_Camera);
		if (hit.bBlockingHit)
		{
			if (hit.GetActor()->Implements<UInteractionInterface>() || (Cast<IInteractionInterface>(hit.GetActor()) != nullptr))
			{
				IInteractionInterface::Execute_OnInteraction(hit.GetActor(), this, hit.GetComponent());
			}
		}
	}
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

	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerBase::OnUse);
}

