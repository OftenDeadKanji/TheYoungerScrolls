// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/InventoryItemPickup.h"

#include "Core/General/Characters/CharacterEx.h"
#include "Core/General/Characters/Components/InventoryComponent.h"
#include "Core/Player/Controllers/MainPlayerController.h"
#include "Inventory/InventoryItem.h"

AInventoryItemPickup::AInventoryItemPickup()
{
	bReplicates = true;

	UStaticMeshComponent* Mesh = GetStaticMeshComponent();
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
}

void AInventoryItemPickup::Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController)
{
	IInteractable::Authority_OnUsePressed_Implementation(PlayerController);

	ACharacterEx* Character = Cast<ACharacterEx>(PlayerController->GetCharacter());

	UInventoryComponent* Inventory = Character->GetComponentByClass<UInventoryComponent>();
	if(Inventory == nullptr)
	{
		return;
	}

	Item->AddSelfToInventory(Inventory);

	Destroy();
}

bool AInventoryItemPickup::IsInteractionByServerRequired_Implementation() const
{
	return true;
}

void AInventoryItemPickup::BeginPlay()
{
	Super::BeginPlay();

	if(Item == nullptr)
	{
		InitItem(true);
	}
}

void AInventoryItemPickup::TryToInitItem()
{
	InitItem(false);
}

void AInventoryItemPickup::InitItem(bool bDestroyOnFail)
{
	if(ItemData.TypeData == nullptr)
	{
		if (bDestroyOnFail)
		{
			Destroy();
		}

		return;
	}

	Item = ItemData.TypeData->CreateItem(this);
	Item->SetCount(ItemData.Count);

	if(Item == nullptr)
	{
		if(bDestroyOnFail)
		{
			Destroy();
		}

		return;
	}

	UStaticMesh* Mesh = Item->GetItemTypeData()->GetStaticMesh();
	UStaticMeshComponent* MeshComponent = GetStaticMeshComponent();

	MeshComponent->SetStaticMesh(Mesh);
}
