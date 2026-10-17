#include <pf/InstallationID.h>
#include <pf/UUID.h>
#include <util/RegistryAccessor.h>

namespace pf //5
{

std::string getInstallationID() //8
{
	util::RegistryAccessor store; //10
	util::JSON& id(store.registry()["fusion"]["installationId"]); //11
	if (!id.isString()) //12
		return UUID().generateUUID(); //13
	return id.getString(); //14
}

}