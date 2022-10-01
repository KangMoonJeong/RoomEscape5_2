#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inspection_Interface.generated.h"

UINTERFACE(MinimalAPI)
class UInspection_Interface : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API IInspection_Interface
{
	GENERATED_BODY()

	
public:
	virtual void StartInteractionSetting() = 0;
	virtual void ClearInteractionSetting() = 0;
};
