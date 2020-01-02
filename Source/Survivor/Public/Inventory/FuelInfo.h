// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "FuelInfo.generated.h"

UENUM(BlueprintType)
enum class EFuelType :uint8
{
    EIT_None UMETA(DisplayName = "None"),
    EIT_Burnable UMETA(DisplayName = "Burnable")
};


USTRUCT(BlueprintType)
struct FFuelInfo
{
    GENERATED_BODY();
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        EFuelType FuelType = EFuelType::EIT_None;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float MaxBurnTime = 5.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float FuelEfficiency = 1.f;
};
