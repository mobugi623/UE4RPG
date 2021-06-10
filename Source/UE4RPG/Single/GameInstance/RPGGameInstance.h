#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

#include "RPGGameInstance.generated.h"

#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObject) (Cast<URPGGameInstance>(worldContextObject->GetGameInstance()))
#endif

UCLASS()
class UE4RPG_API URPGGameInstance final : 
	public UGameInstance
{
	GENERATED_BODY()

private :
	// ����� �Ŵ��� Ŭ���� ��ü���� �����մϴ�.
	TMap<FString, UManagerClass*> ManagerClasses;

private :
	// Manager Class �� ����մϴ�.
	/// - ����� Manager Class �� �ν��Ͻ�ȭ �Ǿ� ManagerClasses Map �� �߰��˴ϴ�.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public :
	// ����� ManagerClass �� ����ϴ�.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{ return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]); }

	// �ּ� �ε��� ���� StreamableManager �� ��� �޼���
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{ return &UAssetManager::GetStreamableManager(); }


public :
	// GameInstance �� �ʱ�ȭ�� �� ȣ��Ǵ� �޼���
	virtual void Init() override;

	// GameInstance �� �Ҹ�� �� ȣ��Ǵ� �޼���
	virtual void Shutdown() override;

};
