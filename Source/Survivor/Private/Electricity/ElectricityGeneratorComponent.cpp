// BSD 2-Clause LicenseCopyright (c) 2019, MetalCat aka Nikita KurguzovAll rights reserved.Redistribution and use in source and binary forms, with or withoutmodification, are permitted provided that the following conditions are met:1. Redistributions of source code must retain the above copyright notice, this   list of conditions and the following disclaimer.2. Redistributions in binary form must reproduce the above copyright notice,   this list of conditions and the following disclaimer in the documentation   and/or other materials provided with the distribution.THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THEIMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AREDISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLEFOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIALDAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS ORSERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVERCAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USEOF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include "Survivor/Public/Electricity/ElectricityGeneratorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "Engine.h"

// Sets default values for this component's properties
UElectricityGeneratorComponent::UElectricityGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UElectricityGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UElectricityGeneratorComponent::GetIsActorConnected(AActor* actor)
{
	if (ConnectedActors.Num() > 0)
	{
		for (int i = 0; i < ConnectedActors.Num(); i++)
		{
			if (ConnectedActors[i] == actor) { return true; }
		}
		return false;
	}
	else
	{
		return false;
	}
	
}

void UElectricityGeneratorComponent::DisconnectActor(AActor* actor)
{
	ConnectedActors.Remove(actor);
}


void UElectricityGeneratorComponent::Update()
{
	TArray<AActor*>Consumers;
	UGameplayStatics::GetAllActorsOfClass(GetOwner()->GetWorld(), BuildingClass, Consumers);
	
	if (Consumers.Num() > 0) 
	{
		bool ShouldUpdate = false;
		TArray<AActor*>ActorsToDisconnect;
		for (int i = 0; i < Consumers.Num(); i++) 
		{
			if (Consumers[i] == GetOwner()) {/*skip*/}
			else if (GetIsActorConnected(Consumers[i]))
			{
				if(FVector::Distance(Consumers[i]->GetActorLocation(), GetOwner()->GetActorLocation()) <= Range){}
				else
				{
					ActorsToDisconnect.Add(Consumers[i]);
				}
			}
			else if (Consumers[i]->GetComponentByClass(ConsumerClass) != nullptr&& FVector::Distance(Consumers[i]->GetActorLocation(),GetOwner()->GetActorLocation()) <= Range)
			{
				if (Cast<UElectricityConsumerComponent>(Consumers[i]->GetComponentByClass(ConsumerClass)) != nullptr)
				{
					ConnectedActors.Add(Consumers[i]);

					Cast<UElectricityConsumerComponent>(Consumers[i]->GetComponentByClass(ConsumerClass))->bHasElectricity = true;
					ShouldUpdate = true;
				}
			}
		/*	else
			{
				
				GEngine->AddOnScreenDebugMessage(-1, UpdateTime, FColor::Red, Consumers[i]->GetFName().ToString());
				GEngine->AddOnScreenDebugMessage(-1,UpdateTime, FColor::Red, Consumers[i]->GetComponentByClass(ConsumerClass) == nullptr?TEXT("Has component!"):TEXT("Doesn't have component!"));
				GEngine->AddOnScreenDebugMessage(-1, UpdateTime, FColor::Red, FVector::Distance(Consumers[i]->GetActorLocation(), GetOwner()->GetActorLocation()) <= Range? TEXT("Close Enough") : FString("Too far away!").Append(FString::FromInt(FVector::Distance(Consumers[i]->GetActorLocation(), GetOwner()->GetActorLocation()))));
			}*/
		}
		for (int i = 0; i < ConnectedActors.Num(); i++)
		{
			if (ConnectedActors[i] == nullptr || !ConnectedActors[i]->IsValidLowLevel()|| ConnectedActors[i]->IsPendingKill())
			{
				ActorsToDisconnect.Add(ConnectedActors[i]);
				ShouldUpdate = true;
				
			}
		}
		if (ActorsToDisconnect.Num() > 0)
		{
			ShouldUpdate = true;
			for (int i = ActorsToDisconnect.Num() - 1; i >= 0; i--)
			{
				DisconnectActor(ActorsToDisconnect[i]);
			}
		}
		if (ShouldUpdate)
		{
			OnConnectedActorsUpdate.Broadcast();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, UpdateTime, FColor::Red, TEXT("No consumers!"));
	}
}

// Called every frame
void UElectricityGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

