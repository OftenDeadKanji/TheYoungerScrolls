// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponTypeData.h"

#include "Inventory/Weapon/WeaponInstanceData.h"

float UWeaponTypeData::GetDamage() const
{
	return Damage;
}

const TSubclassOf<AWeapon>& UWeaponTypeData::GetActorClass() const
{
	return ActorClass;
}

const UStaticMesh* UWeaponTypeData::GetStaticMesh() const
{
	return StaticMesh;
}

UStaticMesh* UWeaponTypeData::GetStaticMesh()
{
	return StaticMesh;
}

const USkeletalMesh* UWeaponTypeData::GetSkeletalMesh() const
{
	return SkeletalMesh;
}

USkeletalMesh* UWeaponTypeData::GetSkeletalMesh()
{
	return SkeletalMesh;
}

const FName& UWeaponTypeData::GetMeshSocketSheathed() const
{
	return MeshSocketSheathed;
}

const UAnimSequence* UWeaponTypeData::GetAnimSheathing() const
{
	return AnimSheathing;
}

const FName& UWeaponTypeData::GetMeshSocketDrawn() const
{
	return MeshSocketDrawn;
}

const UAnimSequence* UWeaponTypeData::GetAnimDrawing() const
{
	return AnimDrawing;
}

UInventoryItemInstanceData* UWeaponTypeData::CreateItem(UObject* Outer)
{
	UWeaponInstanceData* NewItem = NewObject<UWeaponInstanceData>(Outer);
	NewItem->SetItemTypeData(this);
	
	return NewItem;
}
