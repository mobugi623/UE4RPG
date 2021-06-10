#include "BaseSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// ������ ǥ�õ��� �ʵ��� �մϴ�.
	SetSlotItemCount(0);
}

FReply UBaseSlot::NativeOnMouseButtonDown(
	const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	// ���콺 ������ ��ư�� ���ȴٸ�
	if (inMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// ���콺 ������ Ŭ�� �̺�Ʈ �߻�
		OnMouseRightButtonClickedEvent.Broadcast();

		// �̺�Ʈ ó����.
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
}

void UBaseSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	SlotType = slotType;
	InCode = inCode;
}

void UBaseSlot::SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne)
{
	FText countText = FText::FromString(FString::FromInt(itemCount));

	FText itemCountText = (itemCount < 2 && !bVisibleBelowOne) ? FText() : countText;

	Text_Count->SetText(itemCountText);
}
