// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YN_GameMode.generated.h"


class AYN_Player;
class AYN_PlayerController;

UCLASS()
class YOUNG_API AYN_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Default classes")
	TSubclassOf<AYN_Player> DefaultPlayerClass;
	UPROPERTY(EditAnywhere, Category = "Default classes")
	TSubclassOf<AYN_PlayerController> DefaultPlayerControllerClass;
};
