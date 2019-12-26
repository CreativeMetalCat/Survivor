// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/Inventory/DroppedItemBase.h"
#include "Survivor/Public/Inventory/InventoryInterface.h"


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

void ADroppedItemBase::OnInteraction_Implementation(AActor* interactor, UPrimitiveComponent* interactedComponent)
{
	if (interactor != nullptr)
	{
		if (interactor->Implements<UInventoryInterface>() && info.Num() > 0)
		{
			for (int i = 0; i < info.Num(); i++)
			{
				IInventoryInterface::Execute_AddItem(interactor, info[i],true);
			}
			Destroy();
		}
	}
}

FInteractibleActorData ADroppedItemBase::GetDataFromActor_Implementation(bool& HasData)
{
	if (info.Num() > 0)
	{
		HasData = true;
		FString itemNames;
		for (int i = 0; i < info.Num(); i++)
		{
			itemNames.Append(FString(info[i].Name.ToString() + " x " + FString::FromInt(info[i].Amount) + "\n"));
		}
		return FInteractibleActorData(FText::FromString(itemNames), FText());
	}
	else
	{
		HasData = false;
		return FInteractibleActorData();
	}

}

// Called every frame
void ADroppedItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

