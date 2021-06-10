#include "GamePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/WidgetController/WidgetController.h"

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("OpenInventory"), EInputEvent::IE_Pressed,
		this, &ThisClass::OpenInventory);

	// MouseX, Y �Է� �� ȣ���� �޼��带 ���ε���ŵ�ϴ�.
	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::MouseXInput(float axis)
{
	// ��Ʈ�ѷ��� Yaw ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� ���������� �̵���Ų�ٸ� 1
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	// ��Ʈ�ѷ��� Pitch ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� �Ʒ������� �̵���Ų�ٸ� 1
	AddPitchInput(axis);
}

void AGamePlayerController::OpenInventory()
{
	GetManager(UPlayerManager)->GetPlayerInventory()->ToggleInventoryWnd(GetWidgetController());
}
