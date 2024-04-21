// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_PlayerHUD.generated.h"

class UTextBlock;

UCLASS()
class YOUNG_API UYN_PlayerHUD : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	UFUNCTION(BlueprintCallable)
	void UpdateStamina(float CurrentStamina, float MaxStamina);
	UFUNCTION(BlueprintCallable)
	void UpdateMana(float CurrentMana, float MaxMana);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextMana;
};
