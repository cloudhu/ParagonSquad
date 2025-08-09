// CloudHu:604746493@qq.com All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"

#include "BlueprintFunctionLibs/CommonUIExtensions.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_PrimaryLayout.h"

#include "FrontendUISubsystem.generated.h"

struct FStreamableHandle;
class UCommonActivatableWidget;
/**
 * The state of an async load operation for the UI.
 */
enum class EAsyncWidgetLayerState : uint8
{
	Canceled,
	Initialize,
	AfterPush
};

/**
 * 
 */
UCLASS()
class PARAGONSQUAD_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UFrontendUISubsystem* Get(const UObject* WorldContextObject);

	//~ Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerName, bool bSuspendInputUntilComplete,
	                                                          TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass)
	{
		return PushWidgetToLayerStackAsync<ActivatableWidgetT>(LayerName, bSuspendInputUntilComplete, ActivatableWidgetClass,
		                                                       [](EAsyncWidgetLayerState, ActivatableWidgetT*)
		                                                       {
		                                                       });
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerName, bool bSuspendInputUntilComplete,
	                                                          TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass,
	                                                          TFunction<void(EAsyncWidgetLayerState, ActivatableWidgetT*)> StateFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		static FName Name_PushingWidgetToLayer("PushingWidgetToLayer");
		const FName SuspendInputToken = bSuspendInputUntilComplete
			                                ? UCommonUIExtensions::SuspendInputForPlayer(CreatedPrimaryLayout->GetOwningPlayer(), Name_PushingWidgetToLayer)
			                                : NAME_None;

		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSharedPtr<FStreamableHandle> StreamingHandle = StreamableManager.RequestAsyncLoad(
			ActivatableWidgetClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateWeakLambda(
				this,
				[this, LayerName, ActivatableWidgetClass, StateFunc,
					SuspendInputToken]()
				{
					UCommonUIExtensions::ResumeInputForPlayer(
						CreatedPrimaryLayout->GetOwningPlayer(),
						SuspendInputToken);

					ActivatableWidgetT* Widget = PushWidgetToLayerStack<
						ActivatableWidgetT>(
						LayerName, ActivatableWidgetClass.Get(),
						[StateFunc](ActivatableWidgetT& WidgetToInit)
						{
							StateFunc(EAsyncWidgetLayerState::Initialize,
							          &WidgetToInit);
						});

					StateFunc(EAsyncWidgetLayerState::AfterPush, Widget);
				})
		);

		// Set up a cancel delegate so that we can resume input if this handler is canceled.
		StreamingHandle->BindCancelDelegate(FStreamableDelegate::CreateWeakLambda(
				this,
				[this, StateFunc, SuspendInputToken]()
				{
					UCommonUIExtensions::ResumeInputForPlayer(
						CreatedPrimaryLayout->GetOwningPlayer(), SuspendInputToken);
					StateFunc(EAsyncWidgetLayerState::Canceled, nullptr);
				})
		);

		return StreamingHandle;
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, UClass* ActivatableWidgetClass)
	{
		return PushWidgetToLayerStack<ActivatableWidgetT>(LayerName, ActivatableWidgetClass, [](ActivatableWidgetT&)
		{
		});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, UClass* ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (UCommonActivatableWidgetContainerBase* Layer = CreatedPrimaryLayout->FindWidgetStackByTag(LayerName))
		{
			return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
		}

		return nullptr;
	}

	void FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget) const;

private:
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
