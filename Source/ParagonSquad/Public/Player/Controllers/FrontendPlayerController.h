// CloudHu:604746493@qq.com All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PARAGONSQUAD_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()
	AFrontendPlayerController();

protected:
	virtual void OnPossess(APawn* aPawn) override;
};
