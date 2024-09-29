// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/InventoryItem.h"

#include "Net/UnrealNetwork.h"


void UInventoryItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryItem, Data);
	DOREPLIFETIME(UInventoryItem, Count);
}

bool UInventoryItem::IsSupportedForNetworking() const
{
	return true;
}

void UInventoryItem::AddSelfToInventory(UInventoryComponent* Inventory)
{}

const UInventoryItemTypeData* UInventoryItem::GetItemTypeData() const
{
	return Data;
}

void UInventoryItem::SetItemTypeData(UInventoryItemTypeData* InData)
{
	Data = InData;
}

int32 UInventoryItem::GetCount() const
{
	return Count;
}

void UInventoryItem::SetCount(int32 InCount)
{
	Count = InCount;
}

void UInventoryItem::AddCount(int32 InCount)
{
	Count += InCount;
}
