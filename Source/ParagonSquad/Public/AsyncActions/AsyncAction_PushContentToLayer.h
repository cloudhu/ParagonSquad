// CloudHu:604746493@qq.com All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Engine/CancellableAsyncAction.h"
#include "AsyncAction_PushContentToLayer.generated.h"

class APlayerController;
class UCommonActivatableWidget;
class UObject;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPushContentToLayerForPlayerAsyncDelegate, UCommonActivatableWidget*, UserWidget);

/**
 * 
 */
UCLASS()
class PARAGONSQUAD_API UAsyncAction_PushContentToLayer : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:
	virtual void Cancel() override;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"))
	static UAsyncAction_PushContentToLayer* PushContentToLayer(APlayerController* OwningPlayer, UPARAM(meta = (AllowAbstract=false))
	                                                                    TSoftClassPtr<UCommonActivatableWidget> WidgetClass,
	                                                                    UPARAM(meta = (Categories = "Frontend.WidgetStack"))
	                                                                    FGameplayTag LayerName, bool bSuspendInputUntilComplete = true, bool bFocusOnNewlyPushedWidget=false);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate BeforePush;

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate AfterPush;

private:
	FGameplayTag LayerName;
	bool bSuspendInputUntilComplete = false;
	TWeakObjectPtr<APlayerController> OwningPlayerPtr;
	TWeakObjectPtr<UWorld> OwningWorldPtr;
	TSoftClassPtr<UCommonActivatableWidget> WidgetClass;

	TSharedPtr<FStreamableHandle> StreamingHandle;

	bool bCachedFocusOnNewlyPushedWidget = false;
};
