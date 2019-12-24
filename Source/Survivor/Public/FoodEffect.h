// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimerManager.h"

#include "FoodEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVOR_API UFoodEffect : public UObject
{
    GENERATED_BODY()
public:

   

    UFUNCTION(BlueprintPure)
        //To expand unreal engine's limitations
        UWorld* GetActorWorld(AActor* actor);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float LifeTime = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTimerHandle DestractionTimerHadle;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
        void Destroy();

    void Destroy_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
        //To avoid issues with BeginPlay() place everything connected to mesh setup here
        void ApplyEffect(AActor*actorToApplyTo);

    void  ApplyEffect_Implementation(AActor* actorToApplyTo);
};
