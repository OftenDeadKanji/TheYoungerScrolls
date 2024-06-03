// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YN_PlayerController.generated.h"

struct FInputActionValue;

class AYN_Player;
class UYN_InputMappingContext;

UCLASS()
class YOUNG_API AYN_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetupInputComponent() override;

protected:
	void BeginPlay() override;

#pragma region Player Input
	UFUNCTION(BlueprintCallable)
	void CallMove(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void CallLookAround(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CallJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CallStartCrouch(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void CallStopCrouch(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CallInteractPrimary(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void CallInteractSecondary(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CallToggleInventory(const FInputActionValue& Value);

	//UFUNCTION(BlueprintCallable)
	//void CallWidgetMoveFocus(const FInputActionValue& Value);
#pragma endregion
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AYN_Player> PlayerClass;

	UPROPERTY(Replicated)
	TWeakObjectPtr<AYN_Player> PossessedPlayer;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UYN_InputMappingContext> PlayerInputMapping;
};
