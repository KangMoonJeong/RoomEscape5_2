#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction_Interfece.generated.h"

UINTERFACE(MinimalAPI)
class UInteraction_Interfece : public UInterface
{
	GENERATED_BODY()
};

class ROOMESCAPE_API IInteraction_Interfece
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;

};
