// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_InventoryItem.h"
#include "Utilities/DebugMacros.h"

void UYN_InventoryItem::Init()
{
	SafeCheckMsgNoRet(false, TEXT("This function MUST be overridden!"));
}

void UYN_InventoryItem::AddToInventory(UYN_InventoryComponent* Inventory)
{
	SafeCheckMsgNoRet(false, TEXT("This function MUST be overridden!"));
}

const UYN_InventoryItemConstData* UYN_InventoryItem::GetConstData() const
{
	return Data.ConstData;
}

void UYN_InventoryItem::SetConstData(UYN_InventoryItemConstData* NewConstData)
{
	Data.ConstData = NewConstData;
}

int UYN_InventoryItem::GetCount() const
{
	return Data.Count;
}

void UYN_InventoryItem::SetCount(int NewCount)
{
	Data.Count = NewCount;
}

void UYN_InventoryItem::AddCount(int NewCount)
{
	Data.Count += NewCount;
}

void UYN_InventoryItem::IncrementCount()
{
	Data.Count++;
}

void UYN_InventoryItem::DecrementCount()
{
	Data.Count--;
}
