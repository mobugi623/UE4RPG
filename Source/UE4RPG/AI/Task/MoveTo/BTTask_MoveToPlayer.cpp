#include "BTTask_MoveToPlayer.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/EnemyController/EnemyController.h"
#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

using namespace EBTNodeResult;

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(
	UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComponent, nodeMemory);


	// �� ĳ���� ��Ʈ�ѷ��� ����ϴ�.
	AEnemyController* enemyController = Cast<AEnemyController>(ownerComponent.GetAIOwner());
	/// - ownerComponent : �� �ൿ�� ����ϴ� BehaviorTreeComponnet �� ��Ÿ���ϴ�.
	/// - UBehaviorTreeComponent->GetAIOwner() : �� BehaviorTreeComponent �� ������� AIContyroller ��ü�� ��ȯ�մϴ�.

	// �÷��̾� ĳ���� ��ġ�� ��ǥ ��ġ�� �����ϱ� ���Ͽ� �÷��̾� ĳ���͸� ����ϴ�.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerCharacter());

	// Blackboard �� �߰��� Ű(TargetPosition) �� ���� �÷��̾� ĳ������ ��ġ�� �����մϴ�.
	enemyController->GetBlackboardComponent()->SetValueAsVector(
		FName(TEXT("TargetPosition")),
		playerCharacter->GetActorLocation());


	LOG(TEXT("TargetPositiop = %s"), 
		*enemyController->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("TargetPosition"))).ToString());

	// �ൿ ����
	return Succeeded;
}