// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Survivor/Public/Inventory/ItemData.h"
#include "Survivor/Public/InteractionInterface.h"
#include "DroppedItemBase.generated.h"


UCLASS()
class SURVIVOR_API ADroppedItemBase : public AActor,public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	ADroppedItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Meta = (ExposeOnSpawn = true))
		TArray<FItemInfo> info;

	UFUNCTION(BlueprintNativeEvent)
		void OnInteraction(AActor* interactor, UPrimitiveComponent* interactedComponent);

	void OnInteraction(AActor* interactor, UPrimitiveComponent* interactedComponent)

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
