// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/Inventory/BushBase.h"
#include "Engine/StaticMesh.h"
#include "Survivor/Public/Inventory/InventoryInterface.h"
#include "TimerManager.h"

ABushBase::ABushBase(const FObjectInitializer& OI)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BushMesh = OI.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("BushMesh"));
	this->SetRootComponent(BushMesh);

	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 48.f));
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetupAttachment(BushMesh);
}

void ABushBase::Update()
{
	float DeltaTime = 0.01f;
	PassedTime += DeltaTime;
	if (BushMesh != nullptr)
	{
		if (BushMesh->GetStaticMesh() != nullptr)
		{
			BushMesh->SetRelativeScale3D(FVector(0.25f + (0.75f * (PassedTime / RegrowingTime)), 0.25f + (0.75f * (PassedTime / RegrowingTime)), 0.25f + (0.75f * (PassedTime / RegrowingTime))));
		}
	}
	if (PassedTime >= RegrowingTime)
	{
		PassedTime = 0;
		FinishRegrowing();
	}

}

void ABushBase::Die()
{
	if (bCanRegrow)
	{
		if (BushMesh != nullptr)
		{
			if (BushMesh->GetStaticMesh() != nullptr)
			{
				BushMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
				
			}
		}
		bDead = true;
		GetWorld()->GetTimerManager().SetTimer(RegrowingTimerHandle,this,&ABushBase::Update, 0.01f, true);
	}
	else
	{
		Destroy();
	}
}

void ABushBase::FinishRegrowing()
{
	if (BushMesh != nullptr)
	{
		if (BushMesh->GetStaticMesh() != nullptr)
		{
			BushMesh->RelativeScale3D = FVector(1.f, 1.f, 1.f);
		}
	}
	info = DefaultInfo;
	GetWorld()->GetTimerManager().ClearTimer(RegrowingTimerHandle);
}

void ABushBase::BeginPlay()
{
	DefaultInfo = info;
	/*CollisionBox->SetWorldLocation(GetActorLocation() + FVector(0, 0, 60));*/
	SetupModel();
}

void ABushBase::OnInteraction_Implementation(AActor* interactor, UPrimitiveComponent* interactedComponent)
{
	if (interactor->Implements<UInventoryInterface>() || (Cast<IInventoryInterface>(interactor) != nullptr))
	{
		if (info.Num() > 0)
		{
			TArray<int> infoIdsToRemove;
			for (int i = 0; i < info.Num(); i++)
			{
				if (!IInventoryInterface::Execute_AddItem(interactor, info[i], true))
				{
					break;
				}
				else 
				{
					infoIdsToRemove.Add(i);
				}
			}
			if (infoIdsToRemove.Num() > 0)
			{
				for (int i = infoIdsToRemove.Num() - 1; i >= 0; i--)
				{
					info.RemoveAt(infoIdsToRemove[i]);
				}
			}
			if (info.Num() <= 0)
			{
				Die();
			}
		}
	}
}
