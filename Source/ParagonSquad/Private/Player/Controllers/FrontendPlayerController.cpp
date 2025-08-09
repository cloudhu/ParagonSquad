// CloudHu:604746493@qq.com All Rights Reserved


#include "Player/Controllers/FrontendPlayerController.h"

#include "Camera/CameraActor.h"

#include "Kismet/GameplayStatics.h"

AFrontendPlayerController::AFrontendPlayerController()
{
	
}

void AFrontendPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this,ACameraActor::StaticClass(),FName("FrontendCamera"),FoundCameras);

	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}
}
