#pragma once

#include "Engine/DataTable.h"
#include "RE_PasswordTextureStructure.generated.h"

USTRUCT(BlueprintType)
struct ROOMESCAPE_API FRE_PasswordTextureStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	FString TextureFilePath;
	
};
