// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Survivor/Public/Inventory/ItemData.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVOR_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OwnerNotify_ItemAdded(FItemInfo info, bool PickedUp);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OwnerNotify_ItemRemoved(FItemInfo info,int ItemId);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OwnerNotify_ItemDropped(FItemInfo info, int ItemId);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OwnerNotify_ToolRemoved(FItemInfo info);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OwnerNotify_ToolDropped(FItemInfo info);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool AddItem(FItemInfo info,bool PickedUp);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool RemoveItem(FItemInfo info);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool DropItem(FItemInfo info);

	//filling info is unnessesary here but should be done
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		//filling info is unnessesary here but should be done
		void RemoveTool(FItemInfo info);

	//filling info is unnessesary here but should be done
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		//filling info is unnessesary here but should be done
		void DropTool(FItemInfo info);

	// *itemId* is used only when specific item has to be used, if not it MUST be -1
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		// *itemId* is used only when specific item has to be used, if not it MUST be -1
		void UseItem(FItemInfo info, int itemId = -1, bool ShouldBeRemovedAfterUse = false);
};
