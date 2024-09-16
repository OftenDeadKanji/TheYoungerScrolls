// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Player/Characters/UI/Inventory/ItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/InventoryItem.h"

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UInventoryItem* InventoryItem = Cast<UInventoryItem>(ListItemObject);
	if(IsValid(InventoryItem) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - ListItemObject (%s) is not a Inventory Item!"), *GetName(), *ListItemObject->GetName());
		return;
	}

	const UInventoryItemTypeData* ItemTypeData = InventoryItem->GetItemTypeData();
	if(IsValid(ItemTypeData) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - inventory item (%s) doesn't have ItemTypeData!"), *GetName(), *ListItemObject->GetName());
		return;
	}

	ItemImage->SetBrushFromTexture(InventoryItem->GetItemTypeData()->GetIcon());

	if(ItemTypeData->IsStackable())
	{
		ItemCount->SetText(FText::Format(INVTEXT("{0}"), InventoryItem->GetCount()));
	}
	else
	{
		ItemCount->SetText(INVTEXT(""));
	}
}
