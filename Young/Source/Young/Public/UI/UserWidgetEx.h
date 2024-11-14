// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetEx.generated.h"

enum class EPlayerInputMode : uint8;

UCLASS()
class YOUNG_API UUserWidgetEx : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool IsBlockingPawnInput() const;

	UFUNCTION(BlueprintCallable)
	EPlayerInputMode GetRequiredInputMode() const;
protected:
	void UpdateCachedChildrenData(const TArray<const UUserWidgetEx*>& Children);
	void UpdateInputMode();

	UPROPERTY(EditAnywhere, Category = "Config")
	bool bBlockPawnInput = false;
	bool bChildrenBlockPawnInput = false;

	UPROPERTY(EditAnywhere, Category = "Config")
	EPlayerInputMode RequiredInputMode;
	EPlayerInputMode ChildrenRequiredInputMode;
};
