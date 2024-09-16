// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UserInterfaceSubsystem.generated.h"

class UUserWidgetEx;

UCLASS()
class YOUNG_API UUserInterfaceSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UUserWidgetEx* CreateAndPushWidget(TSubclassOf<UUserWidgetEx> WidgetClass);

	template<typename T>
	T* CreateAndPushWidget(TSubclassOf<UUserWidgetEx> WidgetClass);

	UFUNCTION(BlueprintCallable)
	void PopWidget();

	UFUNCTION(BlueprintCallable)
	UUserWidgetEx* GetTopWidget() const;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UUserWidgetEx*> Widgets;
};

template <typename T>
T* UUserInterfaceSubsystem::CreateAndPushWidget(TSubclassOf<UUserWidgetEx> WidgetClass)
{
	T* Widget = Cast<T>(CreateAndPushWidget(WidgetClass));

	return Widget;
}
