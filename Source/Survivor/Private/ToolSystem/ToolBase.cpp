// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/ToolSystem/ToolBase.h"

#include "Kismet/GameplayStatics.h"
#include "Survivor/Public/ToolSystem/ToolSystemInterface.h"

// Sets default values
AToolBase::AToolBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToolMesh"));
	ToolMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ToolMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(ToolMesh);

}

// Called when the game starts or when spawned
void AToolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AToolBase::Use_Implementation()
{
	if (!bHolstered && GetAttachParentActor() != nullptr)
	{
		IToolSystemInterface::Execute_PlayMeleeAttackAnim(GetAttachParentActor());
	}
}

void AToolBase::Holster_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), HolsterSound);
	bHolstered = true;
	ToolMesh->SetVisibility(false);
	IToolSystemInterface::Execute_OnToolHolstered(GetAttachParentActor());
}

void AToolBase::UnHolster_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), UnHolsterSound);
	bHolstered = false;
	ToolMesh->SetVisibility(true);
	IToolSystemInterface::Execute_OnToolUnHolstered(GetAttachParentActor());
}

// Called every frame
void AToolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

