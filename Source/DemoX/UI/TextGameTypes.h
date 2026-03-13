#pragma once

#include "CoreMinimal.h"
#include "TextGameTypes.generated.h"

USTRUCT(BlueprintType)
struct FTextGameOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OptionId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionText;
};
