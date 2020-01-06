// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Survivor/Public/Inventory/ItemData.h"
#include "Survivor/Public/Inventory/InventoryInterface.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, FItemInfo, info, bool, PickedUp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, FItemInfo, info, int, ItemId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToolAdded,FItemInfo, info);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToolRemoved, FItemInfo, info);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDropped, FItemInfo, info, int, ItemId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToolDropped, FItemInfo, info);

UCLASS(meta=(BlueprintSpawnableComponent) )
class SURVIVOR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	bool AddItemUsingSize(int StackSize, int valueToAdd, FItemInfo info, bool PickedUp);

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
		FOnItemRemoved OnItemRemoved;

	UPROPERTY(BlueprintAssignable)
		FOnToolAdded OnToolAdded;

	UPROPERTY(BlueprintAssignable)
		FOnToolRemoved OnToolRemoved;

	UPROPERTY(BlueprintAssignable)
		FOnToolDropped OnToolDropped;

	UPROPERTY(BlueprintAssignable)
		FOnItemDropped OnItemDropped;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FItemInfo>Items;

	FItemInfo ToolInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bHasTool = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* TableWithDefaultItemInfo;

	UFUNCTION(BlueprintPure)
		TArray<FItemInfo> GetAllItemsWithName(FName name);

	UFUNCTION(BlueprintPure)
		int GetAmountOfItemsWithName(FName name);

	UFUNCTION(BlueprintCallable)
		bool AddItem(FItemInfo info, bool PickUp);

	//Removes specified amount of item from the inventory
	//AddToInventory=true if not removed completly
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(FItemInfo info/*if not removed completly*/);

	//Removes specified amount of item from the inventory
	UFUNCTION(BlueprintCallable)
		bool DropItem(FItemInfo info);

	//Removes specified amount of item from the inventory
	UFUNCTION(BlueprintCallable)
		//Removes specified amount of item from the inventory
		//AddToInventory=true if not removed completly
		bool RemoveTool(FItemInfo info, bool AddToInventory);

	//Removes specified amount of item from the inventory
	UFUNCTION(BlueprintCallable)
		bool DropTool(FItemInfo info);

	UFUNCTION(BlueprintCallable)
		bool SetToolInfo(FItemInfo info);

	UFUNCTION(BlueprintCallable)
		FItemInfo GetToolInfo();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
