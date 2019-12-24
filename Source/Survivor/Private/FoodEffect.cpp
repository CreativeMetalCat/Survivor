// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodEffect.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UWorld* UFoodEffect::GetActorWorld(AActor* actor)
{
	return actor->GetWorld();
}

void UFoodEffect::Destroy_Implementation()
{

}

void UFoodEffect::ApplyEffect_Implementation(AActor* actorToApplyTo)
{
	if (actorToApplyTo != nullptr)
	{
		actorToApplyTo->GetWorld()->GetTimerManager().SetTimer(DestractionTimerHadle, this, &UFoodEffect::Destroy, LifeTime);
	}
}
