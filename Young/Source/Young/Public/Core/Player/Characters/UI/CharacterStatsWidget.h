// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "CharacterStatsWidget.generated.h"

class UProgressBar;
struct FCharacterStats;
class UTextBlock;

UCLASS()
class YOUNG_API UCharacterStatsWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Update(const FCharacterStats& Stats);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BarHealth;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BarStamina;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BarMana;
};
