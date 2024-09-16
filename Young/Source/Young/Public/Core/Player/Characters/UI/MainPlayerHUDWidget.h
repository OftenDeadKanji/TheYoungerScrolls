// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "MainPlayerHUDWidget.generated.h"

class UBackgroundBlur;
class UInventoryWidget;
class UOverlay;
class UInventoryComponent;
struct FCharacterStats;
class UCharacterStatsWidget;
class UTextBlock;

UCLASS()
class YOUNG_API UMainPlayerHUDWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void ToggleInventoryWidget(UInventoryComponent* Inventory = nullptr);

	void UpdateCharacterStats(const FCharacterStats& Stats);

	bool IsAnyWidgetBlockingPawnInput() const;
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacterStatsWidget> CharacterStats;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> GameBlur;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> InventoryPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;
};
