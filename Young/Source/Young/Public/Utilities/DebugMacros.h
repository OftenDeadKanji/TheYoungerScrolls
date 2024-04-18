#pragma once

#define CheckMsg(Expression, Message, ...) \
	checkf(Expression, TEXT("Error! Check failed in file %s at line %d: %s"), *FString(__FILE__), __LINE__, ##__VA_ARGS__);

#define CheckMsgNoRet(Expression, Message, ...) \
	ensureAlwaysMsgf(Expression, TEXT("Error! Check failed in file %s at line %d: %s"), *FString(__FILE__), __LINE__, ##__VA_ARGS__);

#define CheckMsgRet(Expression, ReturnValue, Message, ...) \
	if (!(ensureAlwaysMsgf(Expression, TEXT("Error! Check failed in file %s at line %d: %s"), *FString(__FILE__), __LINE__, ##__VA_ARGS__)) \
	{ \
		return ReturnValue; \
	}

#define CheckHasAuthority() \
	checkf(GetOwner()->HasAuthority(), TEXT("Authority method called on client! In file %s at line %d."), *FString(__FILE__), __LINE__);
