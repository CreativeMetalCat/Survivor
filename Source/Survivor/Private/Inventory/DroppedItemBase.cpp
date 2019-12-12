// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/Inventory/DroppedItemBase.h"

// Sets default values
ADroppedItemBase::ADroppedItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADroppedItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADroppedItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

