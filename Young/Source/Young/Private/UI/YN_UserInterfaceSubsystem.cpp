// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/YN_UserInterfaceSubsystem.h"
#include "Kismet/GameplayStatics.h"

UYN_UserWidget* UYN_UserInterfaceSubsystem::CreateAndPushWidget(TSubclassOf<UYN_UserWidget> WidgetClass)
{
	UWorld* World = GetWorld();
	Check(World);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	Check(LocalPlayer);

	APlayerController* PlayerController = LocalPlayer->GetPlayerController(World);
	Check(PlayerController);

	UYN_UserWidget* Widget = CreateWidget<UYN_UserWidget>(PlayerController, WidgetClass);
	CheckMsg(Widget, TEXT("Failed creating widget of class %s"), *WidgetClass->GetName());

	Widget->AddToViewport();

	Widgets.Add(Widget);
	return Widget;
}

void UYN_UserInterfaceSubsystem::PopWidget()
{
	if (Widgets.Num() == 0)
	{
		return;
	}

	Widgets[Widgets.Num() - 1]->RemoveFromParent();

	Widgets.RemoveAt(Widgets.Num() - 1);
}

UYN_UserWidget* UYN_UserInterfaceSubsystem::GetTopWidget()
{
	if (Widgets.Num() == 0)
	{
		return nullptr;
	}

	return Widgets[Widgets.Num() - 1];
}
