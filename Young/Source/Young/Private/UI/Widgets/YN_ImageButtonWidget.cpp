// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/YN_ImageButtonWidget.h"

#include "Components/Button.h"


UImage* UYN_ImageButtonWidget::GetImage()
{
	return Image;
}

void UYN_ImageButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnHovered.AddDynamic(this, &UYN_ImageButtonWidget::OnHoveredIndirect);
}

void UYN_ImageButtonWidget::OnHoveredIndirect()
{
	OnHovered.Broadcast(this);
}
