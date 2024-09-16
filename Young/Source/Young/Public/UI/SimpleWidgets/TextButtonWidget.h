// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "TextButtonWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class YOUNG_API UTextButtonWidget : public UUserWidgetEx
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;
};
