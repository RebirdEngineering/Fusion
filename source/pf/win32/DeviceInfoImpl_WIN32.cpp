#include <pf/DeviceInfo.h>
#include <lang/Format.h>

#include <windows.h>

using namespace lang;

namespace pf
{
	class DeviceInfo::DeviceInfoImpl : public Object //0x0C bytes
	{
	public:
		DeviceInfoImpl()
		{
		}

		~DeviceInfoImpl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		std::string getOSName() const //4C9D40
		{
			return "Windows";
		}

		std::string getOSVersion() const //4C9D70
		{
			OSVERSIONINFOW osvi;
			GetVersionExW(&osvi);

			return Format("{0}.{1}.{2}", osvi.dwBuildNumber, osvi.dwMinorVersion, osvi.dwMinorVersion).format();
		}

		std::string getModel() const //4CA3A0 | TODO
		{
			return getStaticField("Win32_ComputerSystem", "Model");
		}

		std::string getManufacturer() const //4CA470 | TODO
		{
			return getStaticField("Win32_ComputerSystem", "Manufacturer");
		}

		std::string getProduct() const
		{
			return "";
		}

		std::string getPlatform() const
		{
			return "";
		}

		std::string getHardware() const
		{
			return "";
		}

		std::string getABI() const
		{
			return "";
		}

		int getDisplayWidth() const
		{
			return 0;
		}

		int getDisplayHeight() const
		{
			return 0;
		}

		int getDisplayDensityGroup() const
		{
			return 0;
		}

		int getDisplayConfigurationGroup() const
		{
			return 0;
		}

		int getTotalMemory() const
		{
			return 0;
		}

		int getCPUCoreCount() const
		{
			return 0;
		}

		int getCPUSpeed() const
		{
			return 0;
		}

		std::vector<std::string> getCPUFeatures() const;

		std::string getCPUImplementer() const;

		std::string getCPUPart() const;

		std::string getCPUHardware() const;

		std::vector<std::string> getHardwareComponents() const;

		int getPPI() const
		{
			return 80;
		}

	private:
		std::string getStaticField(const std::string& a1, const std::string& a2) const //sub_4C9F80 TODO, recovered name from Android
		{
			/*if (CoInitializeEx(0, 0) < 0)
				return "";

			if (CoInitializeSecurity(0, -1, 0, 0, 0, 3u, 0, 0, 0) < 0 || ) //{4590F811-1D3A-11D0-891F-00AA004B2E24} CLSID_WbemLocator
			{
				CoUninitialize();
				return "";
			}

			IUnknown* proxyBlanket;

			CoSetProxyBlanket(proxyBlanket, )*/

				return "";
		}
	};

#include <pf/common/DeviceInfo.h>

}