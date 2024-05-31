// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "YN_Interactable.generated.h"

class AYN_PlayerController;

UINTERFACE(MinimalAPI)
class UYN_Interactable : public UInterface
{
	GENERATED_BODY()
};

class YOUNG_API IYN_Interactable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUsePressed(AYN_PlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUseReleased(AYN_PlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPrimeryActionPressed(AYN_PlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPrimaryActionReleased(AYN_PlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSecondaryActionPressed(AYN_PlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSecondaryActionReleased(AYN_PlayerController* PlayerController);
};
