#include "CharacterMovementHelperComponent.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

UCharacterMovementHelperComponent::UCharacterMovementHelperComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCharacterMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	MovementComponent = PlayerCharacter->GetCharacterMovement();

	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;
	RunKeyReleased();
}

void UCharacterMovementHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterMovementHelperComponent::InputHorizontal(float axis)
{
	FVector controllerRightVector = Cast<AActor>(PlayerCharacter->GetController())->
		GetActorRightVector();

	PlayerCharacter->AddMovementInput(
		controllerRightVector, axis);
}

void UCharacterMovementHelperComponent::InputVertical(float axis)
{
	// ��Ʈ�ѷ� ȸ���� Yaw ȸ���� ����ϴ�.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Type::X);
	/// - FRotationMatrix : ȸ���� ��ǥ�� ������ �����ϴ� ����� ��Ÿ���ϴ�.
	/// - ������ �μ��� ��� ȸ������ �����ϰ� �ȴٸ�, ĳ������ �߽��� (0, 0, 0) �� ���¿���
	///   �� �࿡ ���� �󸶳� ȸ���Ǿ� �ִ����� ��Ÿ���� �˴ϴ�.
	/// - GetUnitAxis(EAxis) : EAxis �������� ������ ��ȯ�մϴ�.

	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

void UCharacterMovementHelperComponent::RunKeyPressed()
{
	MovementComponent->MaxWalkSpeed = RunSpeed;
}

void UCharacterMovementHelperComponent::RunKeyReleased()
{
	MovementComponent->MaxWalkSpeed = WalkSpeed;
}