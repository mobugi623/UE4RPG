#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"

#include "Struct/EnemyInfo/EnemyInfo.h"

#include "EnemyCharacter.generated.h"

UCLASS()
class UE4RPG_API AEnemyCharacter : 
	public ABaseCharacter
{
	GENERATED_BODY()

private:
	class UDataTable* DT_EnemyInfo;
	class UBehaviorTree* BehaviorTree;

public :
	// �� ĳ���� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Code")
	FName EnemyCode;

	// �� ĳ���� ������ ��Ÿ���ϴ�.
	FEnemyInfo* EnemyInfo;

public :
	AEnemyCharacter();

protected :
	virtual void BeginPlay() override;

public :
	// �� ĳ���͸� �ʱ�ȭ�մϴ�.
	void InitializeEnemyCharacter();

};
