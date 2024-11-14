// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponInstanceData.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Core/Characters/Player/MainPlayer.h"

void UWeaponInstanceData::AddSelfToInventory(UInventoryComponent* Inventory)
{
	Super::AddSelfToInventory(Inventory);

	Inventory->AddWeapon(this);
}

void UWeaponInstanceData::Use_Implementation(APlayerController* Player)
{
	IUsableItem::Use_Implementation(Player);

	AMainPlayer* PlayerCharacter = Player->GetPawn<AMainPlayer>();

	PlayerCharacter->EquipWeapon_RightHand(this);
}
