// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "DataHelpers.generated.h"

USTRUCT(BlueprintType)
struct FLineData
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Start;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector End;

	FLineData() {}
	FLineData(FVector Start, FVector End) :Start(Start), End(End) {}
};
