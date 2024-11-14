// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/InventoryItemInstanceData.h"

#include "Net/UnrealNetwork.h"


void UInventoryItemInstanceData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryItemInstanceData, Data);
	DOREPLIFETIME(UInventoryItemInstanceData, Count);
}

bool UInventoryItemInstanceData::IsSupportedForNetworking() const
{
	return true;
}

void UInventoryItemInstanceData::AddSelfToInventory(UInventoryComponent* Inventory)
{}

const UInventoryItemTypeData* UInventoryItemInstanceData::GetItemTypeData() const
{
	return Data;
}

UInventoryItemTypeData* UInventoryItemInstanceData::GetItemTypeData()
{
	return Data;
}

void UInventoryItemInstanceData::SetItemTypeData(UInventoryItemTypeData* InData)
{
	Data = InData;
}

int32 UInventoryItemInstanceData::GetCount() const
{
	return Count;
}

void UInventoryItemInstanceData::SetCount(int32 InCount)
{
	Count = InCount;
}

void UInventoryItemInstanceData::AddCount(int32 InCount)
{
	Count += InCount;
}
