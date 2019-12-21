// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;


    // ...
}


// Called when the game starts
void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    GetWorld()->GetTimerManager().SetTimer(StatsUpdateTimerHandle, this, &UPlayerStatsComponent::UpdateStats, 0.01f, true);
}


void UPlayerStatsComponent::UpdateStats()
{
    float time = 0.01f;
    if (bHasHunger)
    {
        if (Hunger > 0)
        {
            Hunger -= time * HungerMultiplier;
            if (Hunger < 0) { Hunger = 0; }
        }
        else
        {
            if (!HungerReminderTimerHandle.IsValid())
            {
                GetWorld()->GetTimerManager().SetTimer(HungerReminderTimerHandle, this, &UPlayerStatsComponent::Hungry, RemindIntervalTime + 1.f, true);
            }
            Health -= HungerDamage * time;
        }
    }

    if (bHasThirst)
    {
        if (Thirst > 0)
        {
            Thirst -= time * ThirstMultiplier;
            if (Thirst < 0) { Thirst = 0; }
        }
        else
        {
            if (!ThirstReminderTimerHandle.IsValid())
            {
                GetWorld()->GetTimerManager().SetTimer(ThirstReminderTimerHandle, this, &UPlayerStatsComponent::Thirsty, RemindIntervalTime, true);
            }
            Health -= ThirstDamage * time;
        }
    }

    if (Health <= 0)
    {
        NoHealthLeft();
    }
}

// Called every frame
void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

