// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/Inventory/DroppedItemBase.h"


ADroppedItemBase::ADroppedItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->info = info;
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

