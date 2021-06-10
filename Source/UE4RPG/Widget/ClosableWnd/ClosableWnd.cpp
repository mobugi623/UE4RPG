#include "ClosableWnd.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	bBeClose = false;

	// �巡�� Ÿ���� �ڽ����� �����մϴ�.
	DraggableWndTitle->SetDragTarget(this);

	// â ũ�⸦ �����մϴ�.
	WndSize = FVector2D(500.0f, 600.0f);

	// Ÿ��Ʋ���� �ݱ� ��ư �̺�Ʈ ����
	DraggableWndTitle->GetCloseButton()->OnClicked.AddDynamic(this, &UClosableWnd::CloseThisWnd);
}

void UClosableWnd::SetTitleText(FText newTitleText)
{
	DraggableWndTitle->SetTitleText(newTitleText);
}

void UClosableWnd::CloseThisWnd()
{
	// ���� ó���� â�̶�� ���� X
	if (bBeClose) return;

	WidgetController->CloseWnd(
		/*bAllClose   = */ false, 
		/*closableWnd = */ this);
}

UCanvasPanelSlot* UClosableWnd::GetCanvasPanelSlot() const
{ 
	return Cast<UCanvasPanelSlot>(Slot); 
}
