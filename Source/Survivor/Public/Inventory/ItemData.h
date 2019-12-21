// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "Survivor/Public/Inventory/FuelInfo.h"
#include "ItemData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType :uint8
{
    EIT_Resource UMETA(DisplayName = "Resource"),
    EIT_Food UMETA(DisplayName = "Food"),
    EIT_Tool UMETA(DisplayName = "Tool")
};



USTRUCT(BlueprintType)
struct FItemInfo
{
    GENERATED_BODY();
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FName Name = "none";

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int Amount = 0;

    //Amount of time item was used. Only needed if FDefaultItemInfo for this item has `bCanBeUsedManyTimes = true`
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int HowMuchWasUsed = 0;

    FItemInfo(FName name, int amount) :Name(name), Amount(amount) {}
    FItemInfo() {}
};

USTRUCT(BlueprintType)
struct FDefaultItemInfo : public FTableRowBase
{
    GENERATED_BODY();
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int MaxAmountPerStack = 64;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FName InGameName = "MissingName";

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UTexture2D* Icon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FText Description = FText::FromName("MissingDescription");

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        EItemType ItemType = EItemType::EIT_Resource;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool bCanBeUsedManyTimes = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int HowManyTimesCanBeUsed = 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FFuelInfo FuelInfo;
};
