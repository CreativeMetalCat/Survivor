// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToolSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UToolSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVOR_API IToolSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool IsAttacking();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayMeleeAttackAnim();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnStopAttackingAnim();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Notify_Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnToolHolstered();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnToolUnHolstered();
};
