#include "../N64.h"
#include "../Config.h"
#include "../RSP.h"
#include "../PluginAPI.h"
#include "../GLideNUI/GLideNUI.h"
#include "../mupenplus/GLideN64_mupenplus.h"
#include <DisplayWindow.h>

#include <QFile>
#include <QString>
#include <QDir>
#include <QSettings>

Config config;

void _copyCustomIni()
{
	wchar_t strIniFolderPath[PLUGIN_PATH_SIZE];
	api().FindPluginPath(strIniFolderPath);
	QString file_in = QDir(QString::fromWCharArray(strIniFolderPath)).filePath("GLideN64.custom.ini");
	if (!QFile(file_in).exists())
		return;
	QString file_out = QDir(QString(ConfigGetUserConfigPath())).filePath("GLideN64.custom.ini");
	if (!QFile(file_out).exists()) {
		QFile::copy(file_in, file_out);
		return;
	}
	QSettings settings_in(file_in, QSettings::IniFormat);
	QSettings settings_out(file_out, QSettings::IniFormat);
	if (settings_in.value("version").toInt() > settings_out.value("version").toInt()) {
		QFile(file_out).remove();
		QFile::copy(file_in, file_out);
	}
}

EXPORT void CALL Config_DoConfig(/*HWND hParent*/)
{
	_copyCustomIni();
	wchar_t strIniFolderPath[PLUGIN_PATH_SIZE];
	mbstowcs(&strIniFolderPath[0], ConfigGetUserConfigPath(), PLUGIN_PATH_SIZE);

	ConfigOpen = true;
	const bool bRestart = RunConfig(strIniFolderPath, api().isRomOpen() ? RSP.romname : nullptr);
	if (config.generalEmulation.enableCustomSettings != 0)
		LoadCustomRomSettings(strIniFolderPath, RSP.romname);
	config.validate();
	if (bRestart)
		dwnd().restart();
	ConfigOpen = false;
}

void Config_LoadConfig()
{
	_copyCustomIni();
	wchar_t strIniFolderPath[PLUGIN_PATH_SIZE];
	mbstowcs(&strIniFolderPath[0], ConfigGetUserConfigPath(), PLUGIN_PATH_SIZE);
	LoadConfig(strIniFolderPath);
	if (config.generalEmulation.enableCustomSettings != 0)
		LoadCustomRomSettings(strIniFolderPath, RSP.romname);
	config.validate();
}
