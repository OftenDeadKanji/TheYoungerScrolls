#pragma once

#define Check(Expression) \
	checkf(Expression, TEXT("Error! Check failed in file %s at line %d."), *FString(__FILE__), __LINE__)

#define CheckMsg(Expression, Message, ...) \
	checkf(Expression, TEXT("Error! Check failed in file %s at line %d: \"%s.\""), *FString(__FILE__), __LINE__, *FString(Message), ##__VA_ARGS__)

#define SafeCheckMsgNoRet(Expression, Message, ...) \
	ensureAlwaysMsgf(Expression, TEXT("Error! Check failed in file %s at line %d: \"%s.\""), *FString(__FILE__), __LINE__, *FString(Message), ##__VA_ARGS__)

#define SafeCheckMsgRet(Expression, ReturnValue, Message, ...) \
	if (!ensureAlwaysMsgf(Expression, TEXT("Error! Check failed in file %s at line %d: \"%s.\""), *FString(__FILE__), __LINE__, *FString(Message), ##__VA_ARGS__)) \
	{ \
		return ReturnValue; \
	}

#define CheckHasAuthority() \
	checkf(HasAuthority(), TEXT("Authority method called on client! In file %s at line %d."), *FString(__FILE__), __LINE__)

#define CheckOwnerHasAuthority() \
	checkf(GetOwner()->HasAuthority(), TEXT("Authority method called on client! In file %s at line %d."), *FString(__FILE__), __LINE__)
