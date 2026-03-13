#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextGameOptionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOptionClicked, int32, OptionId);

class UButton;
class UTextBlock;

UCLASS()
class DEMOX_API UTextGameOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOption(int32 InOptionId, const FText& InText);

	UPROPERTY(BlueprintAssignable)
	FOnOptionClicked OnOptionClicked;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OptionButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OptionText;

private:
	int32 OptionId = 0;
};
