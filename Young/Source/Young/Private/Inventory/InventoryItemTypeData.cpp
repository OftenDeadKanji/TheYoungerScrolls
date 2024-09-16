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

UStaticMesh* UInventoryItemTypeData::GetStaticMesh() const
{
	return StaticMesh;
}

UTexture2D* UInventoryItemTypeData::GetIcon() const
{
	return Icon;
}

bool UInventoryItemTypeData::IsStackable() const
{
	return bStackable;
}

UInventoryItem* UInventoryItemTypeData::CreateItem(UObject* Outer)
{
	return nullptr;
}
