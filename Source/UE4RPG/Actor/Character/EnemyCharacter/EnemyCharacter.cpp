#include "EnemyCharacter.h"

#include "Actor/Controller/EnemyController/EnemyController.h"

#include "Single/GameInstance/RPGGameInstance.h"

#include "Engine/DataTable.h"

#include "BehaviorTree/BehaviorTree.h"


AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_EnemyInfo.DT_EnemyInfo'"));
	if (DT_ENEMY_INFO.Succeeded()) DT_EnemyInfo = DT_ENEMY_INFO.Object;

	EnemyCode = FName(TEXT("1000"));

	// ����ϴ� AI Controller �� �����մϴ�.
	AIControllerClass = AEnemyController::StaticClass();

	// Collision Presets �� ���� �����մϴ�.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCharacter"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeEnemyCharacter();

}

void AEnemyCharacter::InitializeEnemyCharacter()
{

	// �� �ڵ带 �̿��Ͽ� �� ������ ����ϴ�.
	FString contextString;
	EnemyInfo = DT_EnemyInfo->FindRow<FEnemyInfo>(EnemyCode, contextString);

	if (EnemyInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter.cpp :: %d LINE :: EnemyInfo is null (EnemyCode = %s)"),
			__LINE__, *EnemyCode.ToString());
		return;
	}

	
	// ���̷�Ż �޽� ����
	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->SkeletalMeshPath));
	/// - LoadSynchronous(target) : target �� �ش��ϴ� �ּ��� ���� ������� �ε��Ͽ� UObject* �������� ��ȯ�մϴ�.

	GetMesh()->SetSkeletalMesh(skeletalMesh);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// �ִ� �̵� �ӷ� ����
	GetCharacterMovement()->MaxWalkSpeed = EnemyInfo->MaxMoveSpeed;

	// ĸ�� ũ�� ����
	GetCapsuleComponent()->SetCapsuleHalfHeight(EnemyInfo->CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(EnemyInfo->CapsuleRadius);

	// BehaviorTree ����
	BehaviorTree = Cast<UBehaviorTree>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->UseBehaviorTreeAssetPath));

	// �ִ� �ν��Ͻ� Ŭ���� ����
	GetMesh()->SetAnimInstanceClass(EnemyInfo->AnimClass);

	// Behavior Tree Run!
	if (IsValid(BehaviorTree))
	{
		Cast<AEnemyController>(GetController())->RunBehaviorTree(BehaviorTree);
	}
}
