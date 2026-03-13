#include "TextGameOptionWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTextGameOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OptionButton)
	{
		OptionButton->OnClicked.AddDynamic(this, &UTextGameOptionWidget::HandleButtonClicked);
	}
}

void UTextGameOptionWidget::SetOption(int32 InOptionId, const FText& InText)
{
	OptionId = InOptionId;
	if (OptionText)
	{
		OptionText->SetText(InText);
	}
}

void UTextGameOptionWidget::HandleButtonClicked()
{
	OnOptionClicked.Broadcast(OptionId);
}
