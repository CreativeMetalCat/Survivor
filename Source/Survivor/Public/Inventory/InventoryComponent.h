// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Survivor/Public/Inventory/ItemData.h"
#include "Survivor/Public/Inventory/InventoryInterface.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVOR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	bool AddItemUsingSize(int StackSize,int valueToAdd,FItemInfo info);

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FItemInfo>Items;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* TableWithDefaultItemInfo;

	UFUNCTION(BlueprintPure)
		TArray<FItemInfo> GetAllItemsWithName(FName name);

	UFUNCTION(BlueprintPure)
		int GetAmountOfItemsWithName(FName name);

	UFUNCTION(BlueprintPure)
		bool HasEnough(FName name, int Amount);

	UFUNCTION(BlueprintCallable)
		bool AddItem(FItemInfo info);

	//Removes specified amount of item from the inventory
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(FItemInfo info);

	//Removes specified amount of item from the inventory
	UFUNCTION(BlueprintCallable)
		bool DropItem(FItemInfo info);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
