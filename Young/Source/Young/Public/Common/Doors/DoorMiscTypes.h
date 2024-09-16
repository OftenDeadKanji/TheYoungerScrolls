// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDoorState : uint8
{
	EOpen,
	EOpening,
	EClosed,
	EClosing
};
