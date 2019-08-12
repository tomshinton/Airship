// Airship Project - Tom Shinton 2018

#pragma once

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
	bool Get(const TArray<FKey>& InChord)
	{
		const int32 ChordIndex = GetDelegateForChord(InChord);
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
	int32 GetDelegateForChord(const TArray<FKey>& InChord) const
	{
		return Defs.IndexOfByPredicate([this, &InChord](const FChordDef& Chord)
		{ 
			return Chord.DoesChordMatch(InChord);
		});
	};

private:

	TArray<FChordDef> Defs;
};
