#include <pf/InstallationID.h>
#include <pf/UUID.h>
#include <util/RegistryAccessor.h>

namespace pf //5
{

std::string getInstallationID() //8
{
	util::RegistryAccessor store; //10
	util::JSON& id(store.registry()["fusion"]["installationId"]); //11
	return id.isString() ? id.getString() : UUID::generateUUID();
}

}