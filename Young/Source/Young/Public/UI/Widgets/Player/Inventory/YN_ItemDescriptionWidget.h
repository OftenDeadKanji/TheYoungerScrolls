// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_ItemDescriptionWidget.generated.h"

class UImage;
class UTextBlock;

class UYN_InventoryItem;

UCLASS()
class YOUNG_API UYN_ItemDescriptionWidget : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:
	void SetNewItem(UYN_InventoryItem* Item);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemTextDescription;
};
