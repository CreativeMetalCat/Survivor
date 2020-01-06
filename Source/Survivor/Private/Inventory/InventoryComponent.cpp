// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor/Public/Inventory/InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObject(TEXT("DataTable'/Game/DataTables/DT_Items.DT_Items'"));
    if (DataTableObject.Succeeded())
    {
        TableWithDefaultItemInfo = DataTableObject.Object;
    }

	// ...
}


bool UInventoryComponent::AddItemUsingSize(int StackSize, int valueToAdd, FItemInfo info, bool PickedUp)
{

    int stackAmount = StackSize;
    for (int i = 0; i < Items.Num(); i++)
    {
        if (Items[i].Name == info.Name && Items[i].Amount < stackAmount)
        {
            if ((stackAmount - Items[i].Amount) < valueToAdd)
            {
                valueToAdd -= (stackAmount - Items[i].Amount);
                Items[i].Amount += (stackAmount - Items[i].Amount);
            }
            else if ((stackAmount - Items[i].Amount) == valueToAdd)
            {
                Items[i].Amount += (stackAmount - Items[i].Amount);
                valueToAdd = 0;
                OnItemAdded.Broadcast(info, PickedUp);              
                return true;
            }
            else
            {
                Items[i].Amount += valueToAdd;
                valueToAdd = 0;
                OnItemAdded.Broadcast(info, PickedUp);               
                return true;
            }
        }
    }
    if (info.Amount > stackAmount)
    {
        TArray<FItemInfo> itemsToAdd;
        int value = valueToAdd;
        while ((value - stackAmount) > 0)
        {
            itemsToAdd.Add(FItemInfo(info.Name, stackAmount));
            value -= stackAmount;
        }
        if (value > 0)
        {

            itemsToAdd.Add(FItemInfo(info.Name, value));
        }

        for (int j = 0; j < itemsToAdd.Num(); j++) { OnItemAdded.Broadcast(itemsToAdd[j], PickedUp); }
        Items.Append(itemsToAdd);
    }
    else
    {
        OnItemAdded.Broadcast(info, PickedUp);
        Items.Add(FItemInfo(info.Name, valueToAdd));
    }
    return true;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


TArray<FItemInfo> UInventoryComponent::GetAllItemsWithName(FName name)
{
	if (Items.Num() > 0)
	{
		TArray<FItemInfo> result;
		for (int i = 0; i < Items.Num(); i++)
		{
			if (Items[i].Name == name)
			{
				result.Add(Items[i]);
			}
		}
		return result;
	}
	return TArray<FItemInfo>();
}

int UInventoryComponent::GetAmountOfItemsWithName(FName name)
{
	if (Items.Num() > 0)
	{
		int result = 0;
		for (int i = 0; i < Items.Num(); i++)
		{
			if (Items[i].Name == name)
			{
				result += Items[i].Amount;
			}
		}
		return result;
	}
	return 0;
}
bool UInventoryComponent::AddItem(FItemInfo info,bool PickedUp)
{
    if (info.Amount > 0)
    {
        if (TableWithDefaultItemInfo != nullptr)
        {
            FString ContextString;
            FDefaultItemInfo* row = TableWithDefaultItemInfo->FindRow<FDefaultItemInfo>(info.Name, ContextString);
            if (row!=nullptr)
            {
                
                
                int stackAmount = row->MaxAmountPerStack;
                int valueToAdd = info.Amount;
                AddItemUsingSize(row->MaxAmountPerStack, info.Amount, info,PickedUp);
            }
            else
            {
                AddItemUsingSize(64, info.Amount, info, PickedUp);
            }
        }
        else
        {
            int stackAmount = 64;
            int valueToAdd = info.Amount;
            AddItemUsingSize(64, info.Amount, info, PickedUp);
            return true;
        }

        return true;
    }
    return true;
}

bool UInventoryComponent::RemoveItem(FItemInfo info)
{
    if (Items.Num() > 0 && info.Amount > 0)
    {

        int value = 0;
        TArray<int> indeciesToRemove;
        for (int i = 0; i < Items.Num(); i++)
        {
            if (Items[i].Name == info.Name)
            {
                if ((info.Amount - value) >= Items[i].Amount)
                {
                    indeciesToRemove.Add(i);
                    value += Items[i].Amount;
                }
                else
                {
                    Items[i].Amount -= (info.Amount - value);
                    value += (info.Amount - value);
                }

                if (value >= info.Amount)
                {

                    for (int o = 0; o < indeciesToRemove.Num(); o++)
                    {
                        OnItemRemoved.Broadcast(Items[indeciesToRemove[o]], indeciesToRemove[o]);
                        Items.RemoveAt(indeciesToRemove[o]);
                    }
                    return true;
                }
            }
        }
        return false;
    }
    return false;
}

bool UInventoryComponent::DropItem(FItemInfo info)
{
    if (Items.Num() > 0 && info.Amount > 0)
    {

        int value = 0;
        TArray<int> indeciesToRemove;
        for (int i = 0; i < Items.Num(); i++)
        {
            if (Items[i].Name == info.Name)
            {
                if ((info.Amount - value) >= Items[i].Amount)
                {
                    indeciesToRemove.Add(i);
                    value += Items[i].Amount;
                }
                else
                {
                    Items[i].Amount -= (info.Amount - value);
                    value += (info.Amount - value);
                }

                if (value >= info.Amount)
                {

                    for (int o = 0; o < indeciesToRemove.Num(); o++)
                    {
                        OnItemDropped.Broadcast(Items[indeciesToRemove[o]], indeciesToRemove[o]);
                        Items.RemoveAt(indeciesToRemove[o]);
                    }
                    return true;
                }
            }
        }
        return false;
    }
    return false;
}


bool UInventoryComponent::RemoveTool(FItemInfo info,bool AddToInventory)
{
    if (!bHasTool) { return false; }
    else 
    {
        bHasTool = false;
        if (GetOwner()->Implements<UInventoryInterface>() || (Cast<IInventoryInterface>(GetOwner()) != nullptr))
        {
            OnToolRemoved.Broadcast(ToolInfo);
        }
        if (AddToInventory)
        {
            AddItem(ToolInfo, false);
        }
        ToolInfo = FItemInfo();
        return true;
    }
}

bool UInventoryComponent::DropTool(FItemInfo info)
{
    if (!bHasTool) { return false; }
    else
    {
        bHasTool = false;
        if (GetOwner()->Implements<UInventoryInterface>() || (Cast<IInventoryInterface>(GetOwner()) != nullptr))
        {
            OnToolDropped.Broadcast(ToolInfo);
        }
        ToolInfo = FItemInfo();
        return true;
    }
}

bool UInventoryComponent::SetToolInfo(FItemInfo info)
{
    if (bHasTool) 
    {
       // AddItem(ToolInfo,false); is now replaced by AddToInventory=true
        RemoveTool(ToolInfo,true);
    }
    ToolInfo = info;
    bHasTool = true;
    
    return true;
}

FItemInfo UInventoryComponent::GetToolInfo()
{
    if (bHasTool) { return ToolInfo; }
    else { return FItemInfo(); }
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

