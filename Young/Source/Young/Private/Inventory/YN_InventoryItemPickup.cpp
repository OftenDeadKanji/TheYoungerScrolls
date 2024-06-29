// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_InventoryItemPickup.h"

#include "Common/Interaction/YN_InteractionAreaComponent.h"
#include "Core/Characters/YN_Character.h"
#include "Core/Controllers/YN_PlayerController.h"
#include "Inventory/YN_InventoryItem.h"
#include "Utilities/DebugMacros.h"
#include "Inventory/YN_InventoryItemConstData.h"

AYN_InventoryItemPickup::AYN_InventoryItemPickup()
{
	bReplicates = true;

	UStaticMeshComponent* Mesh = GetStaticMeshComponent();

	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
}

void AYN_InventoryItemPickup::Authority_OnUsePressed_Implementation(AYN_PlayerController* PlayerController)
{
	Check(Item);
	Check(PlayerController);

	AYN_Character* Character = PlayerController->GetPawn<AYN_Character>();
	Check(Character);

	UYN_InventoryComponent* Inventory = Character->GetInventory();
	Check(Inventory);

	Item->AddToInventory(Inventory);

	Destroy();
}

bool AYN_InventoryItemPickup::RequiresInteractionByServer_Implementation() const
{
	return true;
}

void AYN_InventoryItemPickup::BeginPlay()
{
	Super::BeginPlay();

	if (Item == false)
	{
		InitItem(true);
	}
}

void AYN_InventoryItemPickup::TryToInitItem()
{
	InitItem(false);
}

void AYN_InventoryItemPickup::InitItem(bool bDestroyOnFail)
{
	if (SafeCheckMsgNoRet(ItemData.ConstData, TEXT("No Config Data for %s"), *GetName()) == false && bDestroyOnFail)
	{
		Destroy();
		return;
	}

	Item = ItemData.ConstData->CreateItem(this);
	if (SafeCheckMsgNoRet(Item, TEXT("Failed createing Item for %s"), *GetName()) == false)
	{
		Destroy();
		return;
	}

	Item->SetConstData(ItemData.ConstData);
	Item->SetCount(ItemData.Count);

	GetStaticMeshComponent()->SetStaticMesh(ItemData.ConstData->GetMesh());
}
