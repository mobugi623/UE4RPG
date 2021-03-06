#include "WidgetController.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"



void UWidgetController::ResetInputMode(bool bForceChange)
{
	// bForceChange 가 true 이거나, 열린 위젯의 개수가 존재하지 않는다면 입력 모드 초기화
	if (bForceChange || (AllocatedWidgets.Num() == 0 && AllocatedWnds.Num() == 0))
	{
		// 입력 모드를 초기화
		PlayerController->ChangeInputModeToDefault();

		// 커서 표시 설정
		PlayerController->bShowMouseCursor = PlayerController->GetDefaultCursotVisibility();
	}
}

void UWidgetController::SaveWndPosition(const UClosableWnd* closableWnd)
{
	FString wndClsName = closableWnd->GetClass()->GetName();
	FVector2D wndPosition = closableWnd->GetCanvasPanelSlot()->GetPosition();

	if (PrevClosedWndPositions.Contains(wndClsName))
		PrevClosedWndPositions[wndClsName] = wndPosition;
	else PrevClosedWndPositions.Add(wndClsName, wndPosition);
}

void UWidgetController::InitializeWidgetController(ABasePlayerController* playerController)
{
	PlayerController = playerController;
}

void UWidgetController::AddChildWidget(
	UUserWidget* childWidgetInstance, 
	EInputModeType changeInputMode,
	bool bShowMouseCursor,
	float width, float height)
{
	AllocatedWidgets.Add(childWidgetInstance);

	// 전달할 위젯 객체를 화면에 띄웁니다.
	CanvasPanel_WidgetParent->AddChild(childWidgetInstance);

	// 화면에 띄운 위젯의 크기를 설정합니다.
	Cast<UCanvasPanelSlot>(childWidgetInstance->Slot)->SetSize(FVector2D(width, height));
	/// - widgetInstance->Slot : widgetInstance 의 Slot 객체를 얻습니다.
	/// - 주의 : 슬롯은 항상 화면에 띄워진 후 얻어야 합니다.
	
	// 입력 모드를 설정합니다.
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);

	// 커서의 가시성을 설정합니다.
	PlayerController->bShowMouseCursor = bShowMouseCursor;
}

void UWidgetController::CloseChildWidget(UUserWidget* childWidgetInstance)
{
	AllocatedWidgets.Remove(childWidgetInstance);

	// 위젯을 화면에서 제거합니다.
	CanvasPanel_WidgetParent->RemoveChild(childWidgetInstance);
	//childWidgetInstance->RemoveFromParent();

	// 입력 모드 초기화
	ResetInputMode();
}

UClosableWnd* UWidgetController::CreateWnd(
	TSubclassOf<UClosableWnd> wndClass,
	bool bUsePrevPosition,
	EInputModeType changeInputMode,
	bool bShowMouseCursor,
	float alignmentX, float alignmentY,
	float anchorMinX, float anchorMinY,
	float anchorMaxX, float anchorMaxY)
{

	// 새로운 창 위젯을 생성합니다.
	UClosableWnd* newClosableWnd = CreateWidget<UClosableWnd>(this, wndClass);
	newClosableWnd->WidgetController = this;

	AllocatedWnds.Add(newClosableWnd);

	// CanvasPanel_WndParent 의 자식 위젯으로 추가합니다.
	CanvasPanel_WndParent->AddChild(newClosableWnd);

	// 생성된 창의 슬롯을 얻습니다.
	UCanvasPanelSlot* wndSlot = newClosableWnd->GetCanvasPanelSlot();

	// Ancor, Alignment 설정
	wndSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	wndSlot->SetAlignment(FVector2D(alignmentX, alignmentY));

	// 창 크기 설정
	wndSlot->SetSize(newClosableWnd->WndSize);

	// 이전 창 위치를 사용한다면
	if (bUsePrevPosition)
	{
		// 이전 창 위치가 기록되어 있는지 확인합니다.
		FString wndClsName = newClosableWnd->GetClass()->GetName();
		if (PrevClosedWndPositions.Contains(wndClsName))
		{
			// 창 위치를 이전 위치로 설정합니다.
			wndSlot->SetPosition(PrevClosedWndPositions[wndClsName]);
		}
	}

	// 입력 모드, 커서 표시
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;

	return newClosableWnd;
}

void UWidgetController::CloseWnd(bool bAllClose, UClosableWnd* closableWnd)
{
	// 만약 열린 창이 존재하지 않는다면 실행 X
	if (AllocatedWnds.Num() == 0) return;

	// 모든 창을 닫도록 하였다면
	if (bAllClose)
	{
		for (auto wnd : AllocatedWnds)
		{
			// 닫힘 처리되지 않은 창이라면
			if (!wnd->bBeClose)
			{
				// 창 닫힘 이벤트
				if (wnd->OnWndClosed.IsBound())
					wnd->OnWndClosed.Broadcast();

				// 창의 위치를 저장합니다.
				SaveWndPosition(wnd);

				// 부모 위젯에서 떼어냅니다.
				CanvasPanel_WndParent->RemoveChild(wnd);

				// 닫힘 처리
				wnd->bBeClose = true;
			}
		}

		// 배열을 비웁니다.
		AllocatedWnds.Empty();
	}
	// 특정한 창을 닫도록 하였다면
	else
	{
		// 닫을 창이 지정되지 않았다면 마지막으로 열린 창을 닫습니다.
		closableWnd = (closableWnd == nullptr) ? 
			AllocatedWnds[AllocatedWnds.Num() - 1] : 
			closableWnd;

		// 닫힘 처리되지 않은 창이라면
		if (!closableWnd->bBeClose)
		{

			// 창 닫힘 이벤트
			if (closableWnd->OnWndClosed.IsBound())
				closableWnd->OnWndClosed.Broadcast();

			// 창의 위치를 저장합니다.
			SaveWndPosition(closableWnd);

			// 부모 위젯에서 떼어냅니다.
			CanvasPanel_WndParent->RemoveChild(closableWnd);

			// 닫힘 처리
			closableWnd->bBeClose = true;

			AllocatedWnds.Remove(closableWnd);
		}
	}

	// 입력 모드 초기화
	ResetInputMode();

}

void UWidgetController::SortGridPanelElem(
	UUserWidget* gridPanelElem, 
	int32 maxColumnCount, 
	int32& ref_currentColumnCount)
{
	UGridSlot* gridSlot = Cast<UGridSlot>(gridPanelElem->Slot);

	if (!IsValid(gridSlot))
	{
		UE_LOG(LogTemp, Error, 
			TEXT("%s :: %d LINE :: gridPanelElem isn't located inside the Grid Panel!"), 
			__CLSNAME__, __LINE__);
		
		return;
	}

	// 그리드 행과 열을 설정합니다.
	gridSlot->SetColumn(ref_currentColumnCount % maxColumnCount);
	gridSlot->SetRow(ref_currentColumnCount / maxColumnCount);
	++ref_currentColumnCount;
}
