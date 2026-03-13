#pragma once

#include "CoreMinimal.h"
#include "../UI/TextGameTypes.h"
#include "TextGameDataManager.generated.h"

USTRUCT(BlueprintType)
struct FTextGameNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTextGameOption> Options;
};

/**
 * 测试用数据管理器，内置预设剧情
 */
UCLASS(Blueprintable, BlueprintType)
class DEMOX_API UTextGameDataManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	void Init();

	/** 获取当前节点 */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	bool GetNode(int32 NodeId, FTextGameNode& OutNode) const;

	/** 获取起始节点ID */
	UFUNCTION(BlueprintCallable, Category = "TextGame")
	int32 GetStartNodeId() const { return 0; }

private:
	UPROPERTY()
	TMap<int32, FTextGameNode> Nodes;
};
