// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "ImageButtonWidget.generated.h"

class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnImageButtonHovered, UImageButtonWidget*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnImageButtonUnhovered, UImageButtonWidget*, Widget);

UCLASS()
class YOUNG_API UImageButtonWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	UImage* GetImage() const;

	FOnImageButtonHovered OnHovered;
	FOnImageButtonUnhovered OnUnhovered;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;
};
