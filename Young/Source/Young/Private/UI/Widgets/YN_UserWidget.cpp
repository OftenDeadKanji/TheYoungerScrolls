// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/YN_UserWidget.h"

bool UYN_UserWidget::IsBlockingMovementAndCameraInput() const
{
	return GetVisibility() != ESlateVisibility::Collapsed && bBlockingMovementAndCameraInput;
}
