// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Utilities/YN_InputMappingContext.h"

const UInputAction* UYN_InputMappingContext::GetAction(const FString& ActionName) const
{
	for (const auto& Mapping : Mappings)
	{
		if (Mapping.Action->GetName() == ActionName)
		{
			return Mapping.Action;
		}
	}

	return nullptr;
}
