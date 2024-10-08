// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainPlayerHUD.generated.h"

class AMainPlayer;
class UMainPlayerHUDWidget;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class YOUNG_API AMainPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainPlayerHUD();

	UFUNCTION(BlueprintCallable)
	void ToggleInventory(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	bool IsAnyWidgetBlockingPawnInput() const;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Config|HUD Widget", DisplayName = "HUD Widget Class")
	TSubclassOf<UMainPlayerHUDWidget> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UMainPlayerHUDWidget> HUDWidget;

	TWeakObjectPtr<AMainPlayer> MainPlayer;
};
