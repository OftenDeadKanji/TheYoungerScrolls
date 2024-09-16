// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UInventorySectionWidget;
class UButton;
class UTextBlock;
class UInventoryComponent;

UCLASS()
class YOUNG_API UInventoryWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void Init(UInventoryComponent* Inventory);
	void Clear();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextSectionName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPreviousSection;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonNextSection;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventorySectionWidget> Section;

	TWeakObjectPtr<UInventoryComponent> PlayerInventory;
};
