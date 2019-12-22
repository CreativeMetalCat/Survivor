// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/DroppedItemBase.h"
#include "Components/BoxComponent.h"
#include "BushBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API ABushBase : public ADroppedItemBase
{
    GENERATED_BODY()
private:
    ABushBase();
protected:
    bool bDead = false;

    float PassedTime = 0.f;

    TArray<FItemInfo> DefaultInfo;

    void Update();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* BushMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCanRegrow = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTimerHandle RegrowingTimerHandle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float RegrowingTime = 30.f;

    UFUNCTION(BlueprintPure)
        bool GetIsDead()const { return bDead; }

    UFUNCTION(BlueprintPure)
        float GetPassedTime()const { return PassedTime; }

    UFUNCTION(BlueprintCallable)
        void Die();

    UFUNCTION(BlueprintCallable)
        void FinishRegrowing();

    void BeginPlay()override;

    void OnInteraction_Implementation(AActor* interactor, UPrimitiveComponent* interactedComponent) override;

};
