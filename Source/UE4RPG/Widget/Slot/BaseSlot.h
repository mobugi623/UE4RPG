#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "Enum/SlotType.h"
#include "BaseSlot.generated.h"


DECLARE_EVENT(UBaseSlot, FSlotMouseEvent)

UCLASS(Abstract)
class UE4RPG_API UBaseSlot : 
	public UUserWidget
{
	GENERATED_BODY()
	
public :
	// ���콺 ������ ��ư Ŭ�� �� �߻��ϴ� �̺�Ʈ�Դϴ�.
	FSlotMouseEvent OnMouseRightButtonClickedEvent;

protected :
	// ������ Ÿ���� ��Ÿ���ϴ�.
	ESlotType SlotType;

	// ������ ���԰� �Բ� ���Ǵ� �ڵ带 ��Ÿ���ϴ�.
	/// - ������ �ڵ�, ��ų �ڵ�
	FName InCode;

private :
	UPROPERTY(meta = (BindWidget))
	class UImage * Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage * Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Count;

protected :
	virtual void NativeConstruct() override;

	// ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	/// - FReply : ������ �̺�Ʈ�� ��� ������� ó���Ǿ����� �˸��� ���� ����

public :
	// ������ �ʱ�ȭ�մϴ�.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// ���Կ� ǥ�õǴ� ���ڸ� �����մϴ�.
	/// - itemCount : ǥ�ý�ų ������ ������ �����մϴ�.
	/// - bVisibleBelowOne : 1 ������ ��� ���� ǥ�� ���θ� �����մϴ�.
	void SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne = false);

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }

};
