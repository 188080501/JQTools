#include "PngWarningRemover.h"

// Qt lib import
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace PngWarningRemover;

Manage::Manage()
{ }

Manage::~Manage()
{ }

void Manage::conversationPng()
{
    const auto paths = QFileDialog::getOpenFileNames(
                    nullptr,
                    QStringLiteral( "\u8BF7\u9009\u62E9PNG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                    QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                    "*.png"
                );

    if ( paths.isEmpty() ) { return; }

    for ( const auto &path: paths )
    {
        QImage image( path, "PNG" );

        if ( image.isNull() || !image.save( path ) )
        {
            QMessageBox::warning(
                            nullptr,
                            QStringLiteral( "\u9519\u8BEF" ),
                            QStringLiteral( "\u6587\u4EF6\u6253\u5F00\u5931\u8D25\uFF1A%1" ).arg( path )
                        );
            return;
        }

        QImage image2( image.bits(), image.width(), image.height(), QImage::Format_ARGB32 );

        if ( image2.isNull() || !image2.save( path ) )
        {
            QMessageBox::warning(
                            nullptr,
                            QStringLiteral( "\u9519\u8BEF" ),
                            QStringLiteral( "\u6587\u4EF6\u4FDD\u5B58\u5931\u8D25\uFF1A%1" ).arg( path )
                        );
            return;
        }
    }

    QMessageBox::information(
                    nullptr,
                    QStringLiteral( "\u5B8C\u6210" ),
                    QStringLiteral( "\u6240\u6709PNG\u56FE\u7247\u8F6C\u6362\u5DE5\u4F5C\u5DF2\u7ECF\u5B8C\u6210" )
                );
}
