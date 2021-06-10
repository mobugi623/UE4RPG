#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"

#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(ManagerClassType) (Cast<URPGGameInstance>(GetWorld()->GetGameInstance())->GetManagerClass<ManagerClassType>())
#endif

UCLASS(Abstract)
class UE4RPG_API UManagerClass : public UObject
{
	GENERATED_BODY()

public :
	// �ش� ��ü�� ������ �� ȣ��Ǵ� �޼���
	FORCEINLINE virtual void InitManagerClass() {}

	// �ش� ��ü�� �Ҹ�� �� ȣ��Ǵ� �޼���
	FORCEINLINE virtual void ShutdownManagerClass() {}
	
};
