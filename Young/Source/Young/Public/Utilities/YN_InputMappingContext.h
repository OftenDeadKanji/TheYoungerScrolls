// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "YN_InputMappingContext.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class YOUNG_API UYN_InputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()
	
public:
	const UInputAction* GetAction(const FString& ActionName) const;
};
