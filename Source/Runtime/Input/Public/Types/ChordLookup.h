// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Input/Public/AirInputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(ChordLookupLog, All, All);

#if !UE_BUILD_SHIPPING
DECLARE_STATS_GROUP(TEXT("ChordLookup"), STATGROUP_ChordLookup, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("ChordLookup ~ ChordGet"), STAT_PerformChordGet, STATGROUP_ChordLookup);
#endif //UE_BUILD_SHIPPING

struct FChordDef
{
	FChordDef(const TArray<FKey>& InChord, const TFunction<void()>& InFunc)
		: Chord(InChord)
		, Func(InFunc)
	{};
	
public:

	bool DoesChordMatch(const TArray<FKey>& InChord) const
	{
		if (InChord.Num() != Chord.Num())
		{
			return false;
		}
		else
		{
			for (const FKey& Key : InChord)
			{
				if (!Chord.Contains(Key))
				{
					return false;
				}
			}

			return true;
		}
	}

	void operator()()
	{
		Func();
	};

private:

	bool operator==(const FChordDef& OtherChordDef) const
	{
		return DoesChordMatch(OtherChordDef.Chord);
	};

	TArray<FKey> Chord;
	TFunction<void()> Func;
};

class ChordLookup
{

public:

	ChordLookup()
		: CachedOuter(nullptr)
		, CachedPlayerController(nullptr)
	{
		UE_LOG(ChordLookupLog, Warning, TEXT("Cannot init ChordLookup - cannot fully bind to chords!"));
	}

	ChordLookup(UObject& InOuter)
		: CachedOuter(&InOuter)
		, CachedPlayerController(nullptr)
	{
		if (UAirInputSettings* InputSettings = UAirInputSettings::Get())
		{
			ChordCompliments = InputSettings->ChordCompliments;
		}

		if (UWorld* World = InOuter.GetWorld())
		{
			if (APlayerController* PlayerController = World->GetFirstPlayerController<APlayerController>())
			{
				CachedPlayerController = PlayerController;
			}
		}
		else
		{
			UE_LOG(ChordLookupLog, Warning, TEXT("Could not route outers to World from %s - cannot fully bind to chords"), *InOuter.GetName());
		}
	};

	bool Get(const TArray<FKey>& InChord)
	{
#if !UE_BUILD_SHIPPING
		SCOPE_CYCLE_COUNTER(STAT_PerformChordGet);
#endif //!UE_BUILD_SHIPPING

		TArray<FKey> NewChord = InChord;
		AppendChord(NewChord);

		const int32 ChordIndex = GetDelegateForChord(NewChord);
		if (ChordIndex != INDEX_NONE)
		{
			Defs[ChordIndex]();
			return true;
		}
		return false;
	};

	void Bind(const TArray<FKey>& InChord, const TFunction<void()>& InFunc)
	{
		Defs.Emplace(InChord, InFunc);
	};

private:

	void AppendChord(TArray<FKey>& SourceChord)
	{
		if (CachedPlayerController.Get())
		{
			for (const FKey& ChordCompliment : ChordCompliments)
			{
				if (CachedPlayerController->IsInputKeyDown(ChordCompliment))
				{
					SourceChord.Add(ChordCompliment);
				} 
			}
		}
	}

	int32 GetDelegateForChord(const TArray<FKey>& InChord) const
	{
		return Defs.IndexOfByPredicate([this, &InChord](const FChordDef& Chord)
		{ 
			return Chord.DoesChordMatch(InChord);
		});
	};

	UPROPERTY()
	TWeakObjectPtr<UObject> CachedOuter;

	UPROPERTY()
	TWeakObjectPtr<APlayerController> CachedPlayerController;

	TArray<FChordDef> Defs;

	//Shift, Ctrl and Alt - are these down?
	TArray<FKey> ChordCompliments;
};
