// BSD 2-Clause LicenseCopyright (c) 2019, MetalCat aka Nikita KurguzovAll rights reserved.Redistribution and use in source and binary forms, with or withoutmodification, are permitted provided that the following conditions are met:1. Redistributions of source code must retain the above copyright notice, this   list of conditions and the following disclaimer.2. Redistributions in binary form must reproduce the above copyright notice,   this list of conditions and the following disclaimer in the documentation   and/or other materials provided with the distribution.THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THEIMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AREDISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLEFOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIALDAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS ORSERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVERCAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USEOF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Survivor/Public/Electricity/ElectricityConsumerComponent.h"
#include "ElectricityGeneratorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectedActorsUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVOR_API UElectricityGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElectricityGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool GetIsActorConnected(AActor* actor);

	void DisconnectActor(AActor* actor);

public:	

	UPROPERTY(BlueprintAssignable)
		FOnConnectedActorsUpdate OnConnectedActorsUpdate;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bGenerateWires = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Range = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AActor*>ConnectedActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> BuildingClass=AActor::StaticClass();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UElectricityConsumerComponent> ConsumerClass = UElectricityConsumerComponent::StaticClass();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float UpdateTime=0.1f;

	UFUNCTION(BlueprintCallable)
		void Update();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
