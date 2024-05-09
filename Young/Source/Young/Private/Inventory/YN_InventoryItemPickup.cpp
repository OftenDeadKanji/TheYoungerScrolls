// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_InventoryItemPickup.h"

#include "Core/Characters/YN_Character.h"
#include "Core/Controllers/YN_PlayerController.h"
#include "Inventory/YN_InventoryItem.h"
#include "Utilities/DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Core/GameInstance/YN_GameInstance.h"
#include "Inventory/YN_InventoryItemConstData.h"
#include "Inventory/YN_InventoryItem.h"
#include "Core/GameModes/YN_GameModeGame.h"
#include "Core/GameStates/YN_GameStateGame.h"

void AYN_InventoryItemPickup::OnUsePressed_Implementation(AYN_PlayerController* PlayerController)
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
