#include "Welcome.h"

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
