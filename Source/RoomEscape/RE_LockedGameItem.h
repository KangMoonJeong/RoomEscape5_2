#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RE_LockedGameItem.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_LockedGameItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ARE_LockedGameItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	class UPasswordWidget* PasswordWidget;


};
