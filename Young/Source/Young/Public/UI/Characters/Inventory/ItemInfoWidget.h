// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "ItemInfoWidget.generated.h"

class UTextBlock;
class UImage;
class UInventoryItemInstanceData;

UCLASS()
class YOUNG_API UItemInfoWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void SetNewItem(UInventoryItemInstanceData* Item);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImageItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextItemDescription;
};
