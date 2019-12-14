// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "PlayerStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHungryDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThirstyDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVOR_API UPlayerStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPlayerStatsComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(BlueprintAssignable)
        FOnHungryDelegate OnHungry;

    UPROPERTY(BlueprintAssignable)
        FOnThirstyDelegate OnThirsty;

    UPROPERTY(BlueprintAssignable)
        FOnDeathDelegate OnDeath;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Hunger = 100.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Thirst = 100.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int HungerMultiplier = 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int ThirstMultiplier = 1;

    //Damage that is applied to health when Thirst=0.f
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float ThirstDamage = 3.f;

    //Damage that is applied to health when Hunger=0.f
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float HungerDamage = 5.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Health = 100.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool bHasHunger = true;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool bHasThirst = true;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool bHasHealth = true;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float RemindIntervalTime = 2.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FTimerHandle StatsUpdateTimerHandle;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FTimerHandle HungerReminderTimerHandle;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FTimerHandle ThirstReminderTimerHandle;

    UFUNCTION(BlueprintCallable)
        void UpdateStats();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void NoHealthLeft();

    void NoHealthLeft_Implementation() { OnDeath.Broadcast(); }

    //when hunger is 0
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void Hungry();

    void Hungry_Implementation() { OnHungry.Broadcast(); }

    //when Thirst is 0
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void Thirsty();

    void Thirsty_Implementation() { OnThirsty.Broadcast(); }

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
