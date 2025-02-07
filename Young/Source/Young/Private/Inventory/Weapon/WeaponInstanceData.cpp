// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponInstanceData.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Core/Characters/Player/MainPlayer.h"
#include "Inventory/Weapon/WeaponTypeData.h"

void UWeaponInstanceData::AddSelfToInventory(UInventoryComponent* Inventory)
{
	Super::AddSelfToInventory(Inventory);

	Inventory->AddWeapon(this);
}

void UWeaponInstanceData::Use_Implementation(AController* Player)
{
	IUsableItem::Use_Implementation(Player);

	ACharacterEx* Character = Player->GetPawn<ACharacterEx>();
	if(IsValid(Character) == false)
	{
		return;
	}

	UWeaponTypeData* TypeData = Cast<UWeaponTypeData>(Data);
	check(TypeData);

	EWeaponAllowedHandMode AllowedHandMode = TypeData->GetAllowedHandMode();
	if (AllowedHandMode == EWeaponAllowedHandMode::Any || AllowedHandMode == EWeaponAllowedHandMode::Both || AllowedHandMode == EWeaponAllowedHandMode::RightHand)
	{
		Character->ToggleWeapon_RightHand(this);
	}
}

void UWeaponInstanceData::SetHandMode(EWeaponCurrentHandMode InHandMode)
{
	CurrentHandMode = InHandMode;
}
