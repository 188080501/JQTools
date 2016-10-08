/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "welcome.h"

// Qt lib import
#include <QDesktopServices>
#include <QUrl>

using namespace Welcome;

void Manage::openGitHubLink()
{
    QDesktopServices::openUrl( QUrl( "https://github.com/188080501/JQTools" ) );
}

void Manage::openLatestVersionDownloadLink()
{
    QDesktopServices::openUrl( QUrl( "https://github.com/188080501/JQTools/releases/latest" ) );
}
