#include "DraggableWndTitle.h"

#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"

UDraggableWndTitle::UDraggableWndTitle(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	bIsDragging = false;
	TargetWnd = nullptr;
}

void UDraggableWndTitle::NativePreConstruct()
{
	Super::NativePreConstruct();

	Text_Title->SetText(TitleText);
}

void UDraggableWndTitle::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Draggable->OnPressed.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragStarted);
	Button_Draggable->OnReleased.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragFinished);
}

void UDraggableWndTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (TargetWnd && bIsDragging) DragWidget();
}

void UDraggableWndTitle::DragWidget()
{
	// ���콺 ��ġ�� ����ϴ�.
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	/// - UWidgetLayoutLibrary : ���� ���̾ƿ��� ���õ� ��ƿ�� ���� �޼������ �����ϴ� Ŭ����

	// �巡�� �̵���ų â ������ ������ ����ϴ�.
	UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(TargetWnd->Slot);

	// ���콺�� �̵��� ��ŭ ������ �̵���ŵ�ϴ�.
	DragStartPosition = DragStartPosition + (mousePosition - DragInputPosition);
	targetSlot->SetPosition(DragStartPosition);

	// ���� ������ ���Ͽ� ���� ���콺 ��ġ�� ���Ž�ŵ�ϴ�.
	DragInputPosition = mousePosition;
}

void UDraggableWndTitle::OnWidgetDragStarted()
{
	if (!IsValid(TargetWnd)) return;

	// �Էµ� ���콺 ��ġ�� �����մϴ�.
	DragInputPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	// �巡�� ���� ���� ��ġ�� �����մϴ�.
	DragStartPosition = Cast<UCanvasPanelSlot>(TargetWnd->Slot)->GetPosition();

	bIsDragging = true;
}

void UDraggableWndTitle::OnWidgetDragFinished()
{
	if (!IsValid(TargetWnd)) return;

	bIsDragging = false;
}

void UDraggableWndTitle::SetTitleText(FText newTitleText)
{
	Text_Title->SetText(TitleText = newTitleText);
}
