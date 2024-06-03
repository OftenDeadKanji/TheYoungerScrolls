// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_ImageButtonWidget.generated.h"

class UImage;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnImageButtonHovered, UYN_ImageButtonWidget*, Widget);

UCLASS()
class YOUNG_API UYN_ImageButtonWidget : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:
	FOnImageButtonHovered OnHovered;

	UImage* GetImage();
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnHoveredIndirect();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;
};
