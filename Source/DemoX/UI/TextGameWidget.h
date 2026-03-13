#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextGameTypes.h"
#include "TextGameWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextGameOptionSelected, int32, OptionId);

class UTextBlock;
class UScrollBox;
class UTextGameOptionWidget;
class UTextGameDataManager;

UCLASS()
class DEMOX_API UTextGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 使用内置测试数据启动游戏 */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void StartGame();

	/** 显示文本（带打字机效果） */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void ShowText(const FText& Content);

	/** 显示选项列表 */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void ShowOptions(const TArray<FTextGameOption>& Options);

	/** 跳过打字机效果，立即显示全部文字 */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void SkipTypewriter();

	/** 清空所有内容 */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void ClearAll();

	/** 选项被选中时的回调 */
	UPROPERTY(BlueprintAssignable, Category = "TextGame")
	FOnTextGameOptionSelected OnOptionSelected;

	/** 打字机每字符间隔（秒） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextGame")
	float TypewriterSpeed = 0.05f;

	/** 选项按钮 Widget 类（在蓝图中指定） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextGame")
	TSubclassOf<UTextGameOptionWidget> OptionWidgetClass;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> TextScrollBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ContentText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> OptionsScrollBox;

private:
	void TypewriterTick();

	UFUNCTION()
	void HandleOptionClicked(int32 OptionId);

	FString FullText;
	int32 CurrentCharIndex = 0;
	FTimerHandle TypewriterTimerHandle;
	bool bIsTyping = false;

	/** 打字完成后待显示的选项 */
	TArray<FTextGameOption> PendingOptions;

	UPROPERTY()
	TObjectPtr<UTextGameDataManager> DataManager;

	void NavigateToNode(int32 NodeId);
};
