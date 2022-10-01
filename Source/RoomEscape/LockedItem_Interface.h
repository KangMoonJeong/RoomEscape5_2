#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LockedItem_Interface.generated.h"

UINTERFACE(MinimalAPI)
class ULockedItem_Interface : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API ILockedItem_Interface
{
	GENERATED_BODY()

public:
	virtual void SolevedItem() = 0;
	virtual int32 GetItemNum() = 0;
};
