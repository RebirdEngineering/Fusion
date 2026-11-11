#include <pf/UUID.h>

#include <windows.h>

using namespace lang;

namespace pf
{
	class UUID::Impl : public Object //Only known in ABTrilogii
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		std::string generateUUID() //Inspired by https://github.com/BlueMatthew/WechatExporter/blob/8f8ce412fc57c4c792cb519e9d1fb980e0f58cfd/WechatExporter/core/Utils.cpp#L604 | https://github.com/pierre-cheneau/HogwartsLegacy-SpellCaster/blob/45cf0e484f65edf901a0768a8865b7c7fa6def1e/app/Whisper-Spell/CrowdsourcingUtils.cpp#L71
		{
			RPC_CSTR uuidToConv;
			::UUID uuidRaw;

			UuidCreate(&uuidRaw);
			UuidToStringA(&uuidRaw, &uuidToConv);

			std::string uuid = (char*)uuidToConv;

			RpcStringFreeA(&uuidToConv);

			return uuid;
		}
	};

#include <pf/common/UUID.h>

}