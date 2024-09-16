// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/UserInterfaceSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "UI/UserWidgetEx.h"

UUserWidgetEx* UUserInterfaceSubsystem::CreateAndPushWidget(TSubclassOf<UUserWidgetEx> WidgetClass)
{
	UWorld* World = GetWorld();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	APlayerController* PlayerController = LocalPlayer->GetPlayerController(World);

	UUserWidgetEx* Widget = CreateWidget<UUserWidgetEx>(PlayerController, WidgetClass);
	if(Widget == nullptr)
	{

		return nullptr;
	}


	Widget->AddToViewport();
	Widgets.Add(Widget);

	return Widget;
}

void UUserInterfaceSubsystem::PopWidget()
{
	if(Widgets.IsEmpty())
	{
		return;
	}

	Widgets[Widgets.Num() - 1]->RemoveFromParent();
	Widgets.RemoveAt(Widgets.Num() - 1);
}

UUserWidgetEx* UUserInterfaceSubsystem::GetTopWidget() const
{
	if(Widgets.IsEmpty())
	{
		return nullptr;
	}

	return Widgets[Widgets.Num() - 1];
}
