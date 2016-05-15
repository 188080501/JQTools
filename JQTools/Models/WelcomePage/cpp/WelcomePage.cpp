#include "WelcomePage.h"

// Qt lib import
#include <QDesktopServices>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace WelcomePage;

Manage::Manage()
{ }

Manage::~Manage()
{ }

QString Manage::jqToolsVersion()
{
    return JQTOOLS_VERSIONSTRING;
}

void Manage::openGitHubLink()
{
    QDesktopServices::openUrl( QUrl( "https://github.com/188080501/JQTools" ) );
}

void Manage::openLatestVersionDownloadLink()
{
    QDesktopServices::openUrl( QUrl( "" ) );
}
