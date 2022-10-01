#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemSlotInteraction_Interface.generated.h"

UINTERFACE(MinimalAPI)
class UItemSlotInteraction_Interface : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API IItemSlotInteraction_Interface
{
	GENERATED_BODY()

public:
	virtual void SetChildActorClassFromPath(int32 ItemNum) = 0;
	virtual void ItemSlotOnClikced(int32 ItemNum) = 0;
};
