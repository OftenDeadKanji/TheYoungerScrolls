// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/InventoryItemPickup.h"

#include "Core/Characters/CharacterEx.h"
#include "Core/Characters/Components/InventoryComponent.h"
#include "Core//Controllers/MainPlayerController.h"
#include "Inventory/InventoryItemInstanceData.h"

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

void AInventoryItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(PropertyName == GET_MEMBER_NAME_CHECKED(AInventoryItemPickup, Item))
	{
		if(IsValid(Item) && IsValid(Item->GetItemTypeData()) && IsValid(Item->GetItemTypeData()->GetPickUpMesh()))
		{
			GetStaticMeshComponent()->SetStaticMesh(Item->GetItemTypeData()->GetPickUpMesh());
		}
		else
		{
			GetStaticMeshComponent()->SetStaticMesh(nullptr);
		}
	}
}
