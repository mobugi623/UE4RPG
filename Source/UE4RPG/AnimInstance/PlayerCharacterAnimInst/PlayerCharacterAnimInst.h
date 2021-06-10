#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInst.generated.h"

UCLASS()
class UE4RPG_API UPlayerCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()

protected :
	// �ִ� �ν��Ͻ� Ŭ������ �����ϴ� Pawn ��ü�� ��Ÿ���ϴ�.
	class APlayerCharacter* Owner;

	// ���� ĳ���� �ӷ��� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

public :
	virtual void NativeUpdateAnimation(float dt) override;

	
};
