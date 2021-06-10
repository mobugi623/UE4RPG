#include "RPGGameInstance.h"

#include "Single/PlayerManager/PlayerManager.h"

void URPGGameInstance::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassInstance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);

	ManagerClasses.Add(managerClass->GetName(), managerClassInstance);

	managerClassInstance->InitManagerClass();
}

void URPGGameInstance::Init()
{
	Super::Init();

	RegisterManagerClass(UPlayerManager::StaticClass());
}

void URPGGameInstance::Shutdown()
{

	// �Ҵ�� ��� ManagerClass ���� �����մϴ�.
	for (auto managerClassData : ManagerClasses)
	{
		// nullptr Ȯ��
		if (!managerClassData.Value) continue;

		// �ش� ��ü�� GC �� ���� ������ ��ü���� Ȯ���մϴ�.
		if (!managerClassData.Value->IsValidLowLevel()) continue;

		managerClassData.Value->ShutdownManagerClass();

		// ��ü �Ҹ�
		managerClassData.Value->ConditionalBeginDestroy();
	}
	ManagerClasses.Empty();

	Super::Shutdown();
}
