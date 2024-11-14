// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/InventoryItemTypeData.h"

const FText& UInventoryItemTypeData::GetShortName() const
{
	return ShortName;
}

const FText& UInventoryItemTypeData::GetDescription() const
{
	return Description;
}

UStaticMesh* UInventoryItemTypeData::GetPickUpMesh() const
{
	return PickUpMesh;
}

UTexture2D* UInventoryItemTypeData::GetIcon() const
{
	return Icon;
}

bool UInventoryItemTypeData::IsStackable() const
{
	return bStackable;
}

UInventoryItemInstanceData* UInventoryItemTypeData::CreateItem(UObject* Outer)
{
	return nullptr;
}
