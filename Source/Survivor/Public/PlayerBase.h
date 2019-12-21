// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerBase.generated.h"

UCLASS()
class SURVIVOR_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintImplementableEvent)
		UCameraComponent* GetCamera();

	UFUNCTION(BlueprintImplementableEvent)
		FVector GetCameraWorldLocation();

	UFUNCTION(BlueprintCallable)
		void StartSpinting();

	UFUNCTION(BlueprintCallable)
		void StopSpinting();

	UFUNCTION(BlueprintCallable)
		void StartCrouch();

	UFUNCTION(BlueprintCallable)
		void StopCrouch();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		bool CanSprint();

	bool CanSprint_Implementation();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsSprinting = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DefaultWalkSpeed = 475.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SprintSpeed = 900.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
