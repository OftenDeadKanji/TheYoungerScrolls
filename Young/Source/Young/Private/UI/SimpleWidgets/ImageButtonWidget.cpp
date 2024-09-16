// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/SimpleWidgets/ImageButtonWidget.h"

UImage* UImageButtonWidget::GetImage() const
{
	return Image;
}

void UImageButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
