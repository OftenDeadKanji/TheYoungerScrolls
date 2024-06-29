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
	void Authority_OnUsePressed(AYN_PlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUseReleased(AYN_PlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Authority_OnUseReleased(AYN_PlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool RequiresInteractionByServer() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetMaxFacingHalfAngle() const;
	float GetMaxFacingHalfAngle_Implementation() const;

};
