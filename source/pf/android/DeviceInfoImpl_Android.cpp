#include <pf/DeviceInfo.h>

//TODO

using namespace lang;

namespace pf
{
	class DeviceInfo::DeviceInfoImpl : public Object //0x24 bytes
	{
	public:
		DeviceInfoImpl()
		{
			getCPUInfo();
		}

		~DeviceInfoImpl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		std::string getOSName() const
		{
			return "Android";
		}

		std::string getOSVersion() const
		{
			return getStaticField("android/os/Build$VERSION", "RELEASE");
		}

		std::string getModel() const
		{
			return getStaticField("android/os/Build", "MODEL");
		}

		std::string getManufacturer() const
		{
			return getStaticField("android/os/Build", "MANUFACTURER");
		}

		std::string getProduct() const
		{
			return getStaticField("android/os/Build", "PRODUCT");
		}

		std::string getPlatform() const
		{
			char buf[32];
			strncpy(buf, "ro.board.platform");

			char outBuf[92];
			if (__system_property_get(buf, outBuf));
			return outbuf;

			return "";
		}

		std::string getHardware() const
		{
			return getStaticField("android/os/Build", "HARDWARE");
		}

		std::string getABI() const
		{
			return getStaticField("android/os/Build", "CPU_ABI");
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
			//DIR* dir = opendir("/sys/devices/system/cpu");
			//if (!dir)
			//	return -1;
			//
			//while (readdir(dir))
			//{
			//
			//}

			return 0;
		}

		int getCPUSpeed() const
		{
			return 0;
		}

		std::vector<std::string> getCPUFeatures() const;

		std::string getCPUImplementer() const
		{
			return cpuImplementer18;
		}

		std::string getCPUPart() const
		{
			return cpuPart1C;
		}

		std::string getCPUHardware() const
		{
			return cpuHardware20;
		}

		std::vector<std::string> getHardwareComponents() const
		{
			std::vector out;

			if (sub_480D90("com.sonymobile.floating_touch") || sub_480D90("com.sec.feature.hovering_ui"))
				out.push_back("hover");

			if (sub_480D90("com.sec.feature.spen_usp") || sub_480D90("android.hardware.touchscreen.pen"))
				out.push_back("input.pen");

			if (sub_480D90("android.hardware.audio.low_latency"))
				out.push_back("audio.low_latency");

			if (sub_480D90("android.hardware.bluetooth"))
				out.push_back("bluetooth");

			if (sub_480D90("android.hardware.bluetooth_le"))
				out.push_back("bluetooth_le");

			if (sub_480D90("android.hardware.camera.autofocus"))
				out.push_back("camera.autofocus");

			if (sub_480D90("android.hardware.camera.flash"))
				out.push_back("camera.flash");

			if (sub_480D90("android.hardware.camera.front"))
				out.push_back("camera.front");

			if (sub_480D90("android.hardware.camera.consumerir"))
				out.push_back("camera.consumerir");

			if (sub_480D90("android.hardware.location"))
				out.push_back("location");

			if (sub_480D90("android.hardware.location.gps"))
				out.push_back("location.gps");

			if (sub_480D90("android.hardware.location.network"))
				out.push_back("location.network");

			if (sub_480D90("android.hardware.location.microphone"))
				out.push_back("microphone");

			if (sub_480D90("android.hardware.nfc"))
				out.push_back("nfc");

			if (sub_480D90("android.hardware.nfc.hce"))
				out.push_back("nfc.hce");

			if (sub_480D90("android.hardware.sensor.accelerometer"))
				out.push_back("sensor.accelerometer");

			if (sub_480D90("android.hardware.sensor.barometer"))
				out.push_back("sensor.barometer");

			if (sub_480D90("android.hardware.sensor.compass"))
				out.push_back("sensor.compass");

			if (sub_480D90("android.hardware.sensor.gyroscope"))
				out.push_back("sensor.gyroscope");

			if (sub_480D90("android.hardware.sensor.light"))
				out.push_back("sensor.light");

			if (sub_480D90("android.hardware.sensor.proximity"))
				out.push_back("sensor.proximity");

			if (sub_480D90("android.hardware.sensor.stepcounter"))
				out.push_back("sensor.stepcounter");

			if (sub_480D90("android.hardware.sensor.stepdetector"))
				out.push_back("sensor.stepdetector");

			if (sub_480D90("android.hardware.sensor.telephony"))
				out.push_back("sensor.telephony");

			if (sub_480D90("android.hardware.sensor.telephony.cdma"))
				out.push_back("sensor.telephony.cdma");

			if (sub_480D90("android.hardware.sensor.telephony.gsm"))
				out.push_back("sensor.telephony.gsm");

			if (sub_480D90("android.hardware.touchscreen.multitouch.distinct"))
				out.push_back("touch.dual");

			if (sub_480D90("android.hardware.touchscreen.multitouch.jazzhand"))
				out.push_back("touch.multi");

			if (sub_480D90("android.hardware.usb.accessory"))
				out.push_back("usb.accessory");

			if (sub_480D90("android.hardware.usb.host"))
				out.push_back("usb.host");

			if (sub_480D90("android.hardware.wifi"))
				out.push_back("wifi");

			if (sub_480D90("android.hardware.wifi.direct"))
				out.push_back("wifi_direct");

			return out;
		}

		int getPPI() const //TODO
		{
			return 0;
		}

		static bool sub_480D90(const std::string& buildPropText) //Unknown name
		{
			return false;
		}

	private:

		_DWORD* field_C;
		_DWORD* field_10;
		_DWORD field_14;
		std::string cpuImplementer18;
		std::string cpuPart1C;
		std::string cpuHardware20;

		static void getCPUInfo()
		{
		}

		static void getStaticField(const std::string& propCateg, const std::string& property)
		{
		}
	};

#include <pf/common/DeviceInfo.h>

}