// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputMode.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputMode : uint8
{
	EGameOnly,
	EUIOnly,
	EGameAndUI
};
