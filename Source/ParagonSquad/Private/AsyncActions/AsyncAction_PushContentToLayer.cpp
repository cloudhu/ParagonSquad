// CloudHu:604746493@qq.com All Rights Reserved


#include "AsyncActions/AsyncAction_PushContentToLayer.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"

#include "Subsystems/FrontendUISubsystem.h"

#include "UObject/Stack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AsyncAction_PushContentToLayer)


void UAsyncAction_PushContentToLayer::Cancel()
{
	Super::Cancel();
	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

UAsyncAction_PushContentToLayer* UAsyncAction_PushContentToLayer::PushContentToLayer(APlayerController* OwningPlayer,
                                                                                     TSoftClassPtr<UCommonActivatableWidget> WidgetClass,
                                                                                     FGameplayTag LayerName, bool bSuspendInputUntilComplete,
                                                                                     bool bFocusOnNewlyPushedWidget)
{
	if (WidgetClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("PushContentToLayer was passed a null WidgetClass"), ELogVerbosity::Error);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(OwningPlayer, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAsyncAction_PushContentToLayer* Action = NewObject<UAsyncAction_PushContentToLayer>();
		Action->WidgetClass = WidgetClass;
		Action->OwningPlayerPtr = OwningPlayer;
		Action->OwningWorldPtr = World;
		Action->LayerName = LayerName;
		Action->bSuspendInputUntilComplete = bSuspendInputUntilComplete;
		Action->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
		Action->RegisterWithGameInstance(World);

		return Action;
	}

	return nullptr;
}

void UAsyncAction_PushContentToLayer::Activate()
{
	Super::Activate();

	if (UFrontendUISubsystem* UISubsystem = UFrontendUISubsystem::Get(OwningWorldPtr.Get()))
	{
		TWeakObjectPtr<UAsyncAction_PushContentToLayer> WeakThis = this;
		StreamingHandle = UISubsystem->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(
			LayerName, bSuspendInputUntilComplete, WidgetClass,
			[this, WeakThis](
			EAsyncWidgetLayerState State, UCommonActivatableWidget* Widget)
			{
				if (WeakThis.IsValid())
				{
					switch (State)
					{
					case EAsyncWidgetLayerState::Initialize:
						Widget->SetOwningPlayer(OwningPlayerPtr.Get());
						BeforePush.Broadcast(Widget);
						break;
					case EAsyncWidgetLayerState::AfterPush:
						AfterPush.Broadcast(Widget);
						if (bCachedFocusOnNewlyPushedWidget)
						{
							if (UWidget* WidgetToFocus = Widget->GetDesiredFocusTarget())
							{
								WidgetToFocus->SetFocus();
							}
						}
						SetReadyToDestroy();
						break;
					case EAsyncWidgetLayerState::Canceled:
						SetReadyToDestroy();
						break;
					}
				}
				SetReadyToDestroy();
			});
	}
	else
	{
		SetReadyToDestroy();
	}
}
