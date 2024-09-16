// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Utilities/InputMappingContextEx.h"

const UInputAction* UInputMappingContextEx::GetAction(const FString& ActionName) const
{
	for(const FEnhancedActionKeyMapping& Mapping : Mappings)
	{
		if(Mapping.Action->GetName() == ActionName)
		{
			return Mapping.Action;
		}
	}

	return nullptr;
}
