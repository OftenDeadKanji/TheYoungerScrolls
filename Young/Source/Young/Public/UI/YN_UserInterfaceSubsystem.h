// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "Utilities/DebugMacros.h"
#include "YN_UserInterfaceSubsystem.generated.h"

class UYN_UserWidget;

UCLASS()
class YOUNG_API UYN_UserInterfaceSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UYN_UserWidget* CreateAndPushWidget(TSubclassOf<UYN_UserWidget> WidgetClass);

	template<typename T>
	T* CreateAndPushWidget(TSubclassOf<UYN_UserWidget> WidgetClass)
	{
		T* Widget = Cast<T>(CreateAndPushWidget(WidgetClass));
		CheckMsg(Widget, TEXT("Failed creating widget of class %s"), *WidgetClass->GetName());

		return Widget;
	}

	UFUNCTION(BlueprintCallable)
	void PopWidget();

	UFUNCTION(BlueprintCallable)
	UYN_UserWidget* GetTopWidget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UYN_UserWidget*> Widgets;
};
