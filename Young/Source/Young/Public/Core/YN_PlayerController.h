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
#pragma endregion

	UPROPERTY()
	AYN_Player* PossessedPlayer{};

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UYN_InputMappingContext* PlayerInputMapping{};
};
