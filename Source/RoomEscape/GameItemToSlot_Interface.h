#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameItemToSlot_Interface.generated.h"

UINTERFACE(MinimalAPI)
class UGameItemToSlot_Interface : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API IGameItemToSlot_Interface
{
	GENERATED_BODY()

public:
	//virtual void AddTenLimitItemSlotElement() = 0;
	virtual int GetItemNum() = 0;
};
