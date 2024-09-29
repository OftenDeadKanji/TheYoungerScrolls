// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainPlayerUIComponent.generated.h"

struct FInputActionValue;
class AMainPlayer;
class UMainPlayerHUDWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOUNG_API UMainPlayerUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMainPlayerUIComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleInventory(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	bool IsAnyWidgetBlockingPawnInput() const;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainPlayerHUDWidget> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UMainPlayerHUDWidget> HUDWidget;

	TWeakObjectPtr<AMainPlayer> OwnerMainPlayer;
};
