#include "RE/N/NiObject.h"

#include "RE/N/NiRTTI.h"
#include "RE/N/NiStream.h"

namespace RE
{
	const NiRTTI* NiObject::GetRTTI() const
	{
		static REL::Relocation<const NiRTTI*> rtti{ NiObject::Ni_RTTI };
		return rtti.get();
	}

	bool NiObject::RegisterStreamables(NiStream& a_stream)
	{
		return a_stream.RegisterSaveObject(this);
	}

	bool NiObject::IsEqual(NiObject* a_object)
	{
		return a_object != nullptr && std::strcmp(GetRTTI()->GetName(), a_object->GetRTTI()->GetName()) == 0;
	}

	void NiObject::ProcessClone(NiCloningProcess& a_cloning)
	{
		using func_t = decltype(&NiObject::ProcessClone);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68838, 70190) };
		return func(this, a_cloning);
	}

	void NiObject::CreateDeepCopy(NiPointer<NiObject>& a_object)
	{
		using func_t = decltype(&NiObject::CreateDeepCopy);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68839, 70191) };
		return func(this, a_object);
	}
}
