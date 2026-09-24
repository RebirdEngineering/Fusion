#include <pf/AppSettings.h>
#include <lang/Exception.h>

using namespace lang;

namespace pf
{

class AppSettings::AppSettingsImpl : //OSX, Android, PC
    public Object
{
public:
    AppSettingsImpl()
    {
    }

    ~AppSettingsImpl()
    {
    }

    bool isSupported()
    {
        return false;
    }

    bool isBoolean(const std::string& key) const
    {
        return false;
    }

    bool isString(const std::string& key) const
    {
        return false;
    }

    bool isNumber(const std::string& key) const
    {
        return false;
    }

    bool getBoolean(const std::string& key) const
    {
        throwError(Exception(Format("AppSettings::getBoolean not supported")));
        return false;
    }

    double getNumber(const std::string& key) const
    {
        throwError(Exception(Format("AppSettings::getNumber not supported")));
        return 0.0;
    }

    std::string getString(const std::string& key) const
    {
        throwError(Exception(Format("AppSettings::getString not supported")));
        return "";
    }
};

#include <pf/common/AppSettings.h> //Yeah

}