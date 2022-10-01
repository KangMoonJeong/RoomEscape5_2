#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Save_Interface.generated.h"

UINTERFACE(MinimalAPI)
class USave_Interface : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API ISave_Interface
{
	GENERATED_BODY()

public:
	virtual void SaveData() = 0;

};
