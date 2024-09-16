// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputMappingContextEx.generated.h"

UCLASS()
class YOUNG_API UInputMappingContextEx : public UInputMappingContext
{
	GENERATED_BODY()

public:
	const UInputAction* GetAction(const FString& ActionName) const;
};
