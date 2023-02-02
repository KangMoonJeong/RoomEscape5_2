#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RE_PlayerController.generated.h"


UENUM()
enum class EInputMode : uint8
{
	EIM_GameOnly,
	EIM_UIOnly,
	EIM_GameandUI,
	EIM_SavedStatus
};


UCLASS()
class ROOMESCAPE_API ARE_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void BeginPlay() override;






	/* Initialize Level */
private:
	void InitializeLevelData();

	FString StartMapName = FString("StartMap");
	//FString HouseMapName = FString("AlchemistsHouse");
	FString HouseMapName = FString("House");






	/* Access HUD->Item Slot Bar */
public:
	void AddSlotToHUDItemBarWidget();
	void GetHUDInitializeSlotBar();





	/* Press Item Slot */
	void DeliverSlotLocation(int32 PressLocation);
	void ReleaseSlotLocation();






	/* Toggle Game Widget */
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	class URE_HUD* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> StartWidgetClass;

	UPROPERTY()
	class UStartWidget* StartWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> RE_WholeWidgetlass;

	UPROPERTY()
	class URE_WholeWidget* RE_WholeWidget;


protected:
	void OpenAlchemistsHouseWidget();
	void OpenStartMapWidget();

public:
	void SetInputmodeandCursor(EInputMode EStatus);
	void OnCurrentWidgetOffHUD(UUserWidget* OnCurrentWidget, EInputMode EStatus);
	void OnHUDOffCurrentWidget(UUserWidget* SetCurrentWidget = nullptr);

private:
	bool bCurrentHiddenWholeWidget = true;
	bool bCurrentHiddenDialogueWidget = true;

	UUserWidget* CurrentWidget;
	EInputMode EInputModeStatus;






	/* Save Game */
private:
	class URE_SaveGame* SaveGame;
	int32 SelectedIndex = 0;
	
	TMap<int32, bool> QuestNumMap = {};
	
	int32 CurrentChpaterIndex;
	int32 CurrentQuestIndex;

private:
	void InitializeGameData();

public:
	void SaveGameData();
	void LoadSelectedSaveGameSlot();
	void DeleteGameData();


	int32 LoveCount;

	class URE_DialogueWidget* DialogueWidget;


	UPROPERTY()
	FString LocalString;
	void SetLocalString(FString SetLocalString);

	FString GetLocalString();
};