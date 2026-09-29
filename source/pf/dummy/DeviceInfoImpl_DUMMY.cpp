#include <pf/DeviceInfo.h>

using namespace lang;

namespace pf
{
	class DeviceInfo::DeviceInfoImpl : public Object //Legacy OSX, only here as a failsafe.
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

		std::string getOSName() const
		{
			return "Unknown";
		}

		std::string getOSVersion() const
		{
			return "Unknown";
		}

		std::string getModel() const
		{
			return "Unknown";
		}

		std::string getManufacturer() const
		{
			return "Unknown";
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

	};

#include <pf/common/DeviceInfo.h>

}