// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/Player/Inventory/YN_ItemsGridWidget.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"

#include "Inventory/YN_InventoryItem.h"
#include "Inventory/YN_InventoryItemConstData.h"
#include "UI/Widgets/YN_ImageButtonWidget.h"

void UYN_ItemsGridWidget::NativeConstruct()
{
	Grid->SetColumnFill(ColumnsCount, 1.0f / ColumnsCount);
	Grid->SetRowFill(RowsCount, 1.0f / RowsCount);
}

void UYN_ItemsGridWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UYN_ItemsGridWidget::Init(const TArray<UYN_InventoryItem*>& NewItems)
{
	Items = &NewItems;

	Grid->ClearChildren();
	ItemImageButtons.Empty();
	for (int i = 0; i < ColumnsCount; i++)
	{
		for (int j = 0; j < RowsCount; j++)
		{
			int Index = j * ColumnsCount + i;
			if (Index < Items->Num())
			{
				UYN_ImageButtonWidget* ItemImage = CreateWidget<UYN_ImageButtonWidget>(this, ImageButtonWidgetClass);
				ItemImageButtons.Add(ItemImage);

				UYN_InventoryItem* Item = (*Items)[Index];
				ItemImage->GetImage()->SetBrushFromTexture(Item->GetConstData()->GetIcon());

				Grid->AddChildToGrid(ItemImage, j, i);

				ItemImage->OnHovered.AddDynamic(this, &UYN_ItemsGridWidget::ItemHovered);
			}

		}
	}
}

void UYN_ItemsGridWidget::Clear()
{
	Grid->ClearChildren();
}

UYN_InventoryItem* UYN_ItemsGridWidget::GetSelectedItem() const
{
	return SelectedItemIndex < Items->Num() ? (*Items)[SelectedItemIndex] : nullptr;
}

void UYN_ItemsGridWidget::ItemHovered(UYN_ImageButtonWidget* Widget)
{
	for(int i = 0; i < ItemImageButtons.Num(); i++)
	{
		UWidget* Child = ItemImageButtons[i];
		if(Child == Widget)
		{
			SelectedItemIndex = i;
			OnItemHovered.Broadcast((*Items)[i]);
		}
	}
}
