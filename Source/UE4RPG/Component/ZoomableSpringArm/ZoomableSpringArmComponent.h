#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZoomableSpringArmComponent.generated.h"

UCLASS()
class UE4RPG_API UZoomableSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private :
	bool bUseZoom;
	float ArmLengthTarget;
	float ArmLengthMin;
	float ArmLengthMax;

public :
	UZoomableSpringArmComponent();

protected :
	virtual void BeginPlay() override;

public :
	virtual void TickComponent(
		float dt, 
		ELevelTick tickType, 
		FActorComponentTickFunction* thisTickFunction) override;

private :
	// ���� �ε巴�� �̷�������� �մϴ�.
	void SmoothZoomSpringArm(float dt);

public :
	// ī�޶� ���� �����մϴ�.
	void ZoomCamera(float axis);

	// ���� ������ �ּ�, �ִ� �Ÿ��� �����մϴ�.
	FORCEINLINE void SetArmLengthMinMax(float min, float max)
	{
		ArmLengthMin = min;
		ArmLengthMax = max;
	}
};
