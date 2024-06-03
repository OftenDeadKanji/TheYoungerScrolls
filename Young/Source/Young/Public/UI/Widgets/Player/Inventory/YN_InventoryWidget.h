// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_InventoryWidget.generated.h"

class UButton;
class UTextBlock;

class UYN_InventoryComponent;
class UYN_InventorySectionWidget;

UCLASS()
class YOUNG_API UYN_InventoryWidget : public UYN_UserWidget
{
	GENERATED_BODY()

	// SECTIONS ORDER:
	// WEAPONS -> ALL -> WEAPONS...
	
public:
	void Init(UYN_InventoryComponent* Inventory);
	void Clear();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SectionName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PreviousSectionButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NextSectionButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYN_InventorySectionWidget> Section;

	TWeakObjectPtr<UYN_InventoryComponent> PlayerInventory;
};
