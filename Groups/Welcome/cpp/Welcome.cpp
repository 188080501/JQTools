#include "Welcome.h"

// Qt lib import
#include <QDesktopServices>
#include <QUrl>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace Welcome;

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
    QDesktopServices::openUrl( QUrl( "https://github.com/188080501/JQTools/tree/master/bin" ) );
}
