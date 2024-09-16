// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AMainPlayerController;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class YOUNG_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Local_OnUsePressed(AMainPlayerController* PlayerController);
	virtual void Local_OnUsePressed_Implementation(AMainPlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Authority_OnUsePressed(AMainPlayerController* PlayerController);
	virtual void Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetMaxFacingHalfAngle() const;
	virtual float GetMaxFacingHalfAngle_Implementation() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsInteractionByServerRequired() const;
	virtual bool IsInteractionByServerRequired_Implementation() const;

};
