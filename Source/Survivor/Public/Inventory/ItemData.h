// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemInfo
{
    GENERATED_BODY();
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FName Name = "none";

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int Amount = 0;

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

    UPROPERTY(BlueprintReadWrite)
        FText Description = FText::FromName("MissingDescription");
};
