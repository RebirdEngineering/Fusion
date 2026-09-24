AppSettings::AppSettings()
{
	m_impl = new AppSettingsImpl(); //8
}

AppSettings::~AppSettings() //12
{
}

bool AppSettings::isSupported()
{
	return m_impl->isSupported();
}

bool AppSettings::isBoolean(const std::string& key) const //20
{
	return m_impl->isBoolean(key.c_str()); //22
}

bool AppSettings::isString(const std::string& key) const //30
{
	return m_impl->isString(key.c_str()); //32
}

bool AppSettings::isNumber(const std::string& key) const
{
	return m_impl->isNumber(key.c_str());
}

bool AppSettings::getBoolean(const std::string& key) const //35
{
	return m_impl->getBoolean(key.c_str()); //37
}

double AppSettings::getNumber(const std::string& key) const
{
	return m_impl->getNumber(key.c_str());
}

std::string AppSettings::getString(const std::string& key) const //40
{
	return m_impl->getString(key.c_str()); //42
}