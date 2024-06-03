// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_InventoryItemConstData.h"
#include <Utilities/DebugMacros.h>
#include "Inventory/YN_InventoryItem.h"

const FText& UYN_InventoryItemConstData::GetShortName() const
{
	return ShortName;
}

const FText& UYN_InventoryItemConstData::GetDescription() const
{
	return Description;
}

UStaticMesh* UYN_InventoryItemConstData::GetMesh() const
{
	return Mesh;
}

UTexture2D* UYN_InventoryItemConstData::GetIcon() const
{
	return Icon;
}

bool UYN_InventoryItemConstData::IsStackable() const
{
	return bStackable;
}

float UYN_InventoryItemConstData::GetMass() const
{
	return Mass;
}

UYN_InventoryItem* UYN_InventoryItemConstData::CreateItem(UObject* Outer)
{
	SafeCheckMsgNoRet(false, TEXT("This function MUST be overridden!"));
	return nullptr;
}
