// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "ToolBase.generated.h"

UENUM(BlueprintType)
enum class EToolUseAnimType :uint8
{
	ETUAT_None UMETA(DisplayName = "None"),
	ETUAT_SwingLow UMETA(DisplayName = "SwingLow"),
	ETUAT_SwingHigh UMETA(DisplayName = "SwingHigh")
};

UCLASS()
class SURVIVOR_API AToolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UStaticMeshComponent* ToolMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bHolstered = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USoundBase* HolsterSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USoundBase* UnHolsterSound;

	// Sets default values for this actor's properties
	AToolBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Use();

	void Use_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Holster();

	void Holster_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UnHolster();

	void UnHolster_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AnimNotify_Attack();

	void AnimNotify_Attack_Implementation() {}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
