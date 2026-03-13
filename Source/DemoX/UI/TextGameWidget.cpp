#include "TextGameWidget.h"
#include "TextGameOptionWidget.h"
#include "../Data/TextGameDataManager.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "TimerManager.h"

void UTextGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTextGameWidget::ShowText(const FText& Content)
{
	// 停止之前的打字机
	if (bIsTyping)
	{
		GetWorld()->GetTimerManager().ClearTimer(TypewriterTimerHandle);
	}

	// 隐藏选项区域
	if (OptionsScrollBox)
	{
		OptionsScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	}

	FullText = Content.ToString();
	CurrentCharIndex = 0;

	if (TypewriterSpeed <= 0.f)
	{
		// 速度为0，直接显示全部文字
		bIsTyping = false;
		if (ContentText)
		{
			ContentText->SetText(Content);
		}
		if (PendingOptions.Num() > 0)
		{
			TArray<FTextGameOption> Options = MoveTemp(PendingOptions);
			ShowOptions(Options);
		}
		return;
	}

	bIsTyping = true;

	if (ContentText)
	{
		ContentText->SetText(FText::GetEmpty());
	}

	// 启动打字机 Timer
	GetWorld()->GetTimerManager().SetTimer(
		TypewriterTimerHandle,
		this,
		&UTextGameWidget::TypewriterTick,
		TypewriterSpeed,
		true
	);
}

void UTextGameWidget::ShowOptions(const TArray<FTextGameOption>& Options)
{
	if (bIsTyping)
	{
		// 打字还没结束，先存起来，打字完成后自动显示
		PendingOptions = Options;
		return;
	}

	if (!OptionsScrollBox || !OptionWidgetClass)
	{
		return;
	}

	OptionsScrollBox->ClearChildren();

	for (const FTextGameOption& Option : Options)
	{
		UTextGameOptionWidget* OptionWidget = CreateWidget<UTextGameOptionWidget>(this, OptionWidgetClass);
		if (OptionWidget)
		{
			OptionWidget->SetOption(Option.OptionId, Option.OptionText);
			OptionWidget->OnOptionClicked.AddDynamic(this, &UTextGameWidget::HandleOptionClicked);
			OptionsScrollBox->AddChild(OptionWidget);
		}
	}

	OptionsScrollBox->SetVisibility(ESlateVisibility::Visible);
}

void UTextGameWidget::SkipTypewriter()
{
	if (!bIsTyping)
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(TypewriterTimerHandle);
	bIsTyping = false;

	if (ContentText)
	{
		ContentText->SetText(FText::FromString(FullText));
	}

	// 如果有待显示的选项，立即显示
	if (PendingOptions.Num() > 0)
	{
		TArray<FTextGameOption> Options = MoveTemp(PendingOptions);
		ShowOptions(Options);
	}
}

void UTextGameWidget::ClearAll()
{
	if (bIsTyping)
	{
		GetWorld()->GetTimerManager().ClearTimer(TypewriterTimerHandle);
		bIsTyping = false;
	}

	FullText.Empty();
	CurrentCharIndex = 0;
	PendingOptions.Empty();

	if (ContentText)
	{
		ContentText->SetText(FText::GetEmpty());
	}

	if (OptionsScrollBox)
	{
		OptionsScrollBox->ClearChildren();
		OptionsScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTextGameWidget::TypewriterTick()
{
	if (CurrentCharIndex >= FullText.Len())
	{
		// 打字完成
		GetWorld()->GetTimerManager().ClearTimer(TypewriterTimerHandle);
		bIsTyping = false;

		// 显示待显示的选项
		if (PendingOptions.Num() > 0)
		{
			TArray<FTextGameOption> Options = MoveTemp(PendingOptions);
			ShowOptions(Options);
		}
		return;
	}

	CurrentCharIndex++;
	if (ContentText)
	{
		ContentText->SetText(FText::FromString(FullText.Left(CurrentCharIndex)));
	}

	// 自动滚动到底部
	if (TextScrollBox)
	{
		TextScrollBox->ScrollToEnd();
	}
}

void UTextGameWidget::HandleOptionClicked(int32 OptionId)
{
	OnOptionSelected.Broadcast(OptionId);

	// 如果有 DataManager，自动跳转到下一个节点
	// OptionId == -1 表示结局，不再跳转
	if (DataManager && OptionId >= 0)
	{
		NavigateToNode(OptionId);
	}
}

void UTextGameWidget::StartGame()
{
	DataManager = NewObject<UTextGameDataManager>(this);
	DataManager->Init();
	NavigateToNode(DataManager->GetStartNodeId());
}

void UTextGameWidget::NavigateToNode(int32 NodeId)
{
	if (!DataManager)
	{
		return;
	}

	FTextGameNode Node;
	if (DataManager->GetNode(NodeId, Node))
	{
		ShowText(Node.Content);
		ShowOptions(Node.Options);
	}
}
