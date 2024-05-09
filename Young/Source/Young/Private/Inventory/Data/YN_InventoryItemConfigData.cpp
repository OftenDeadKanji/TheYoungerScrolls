// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#include "Inventory/Data/YN_InventoryItemConfigData.h"

const FText& UYN_InventoryItemConfigData::GetName() const
{
    return Name;
}

const FText& UYN_InventoryItemConfigData::GetDescription() const
{
    return Description;
}

UStaticMesh* UYN_InventoryItemConfigData::GetMesh() const
{
    return Mesh;
}

UTexture2D* UYN_InventoryItemConfigData::GetIcon() const
{
    return Icon;
}

bool UYN_InventoryItemConfigData::IsStackable() const
{
    return bStackable;
}

float UYN_InventoryItemConfigData::GetMass() const
{
    return MassInKg;
}
