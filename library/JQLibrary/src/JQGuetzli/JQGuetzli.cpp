#include "JQGuetzli.h"

// Qt lib import
#include <QFileInfo>
#include <QElapsedTimer>

// guetzli lib import
#include <cstdio>
#include <memory>
#include <string>
#include <string.h>
#include "guetzli/processor.h"
#include "guetzli/quality.h"
#include "guetzli/stats.h"

static const bool verbose = false;
static const double quality = 95;

std::string JQGuetzli_ReadFile(FILE* f) {
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("fseek");
        return { };
    }
    off_t size = ftell(f);
    if (size < 0) {
        perror("ftell");
        return { };
    }
    if (fseek(f, 0, SEEK_SET) != 0) {
        perror("fseek");
        return { };
    }
    std::unique_ptr<char[]> buf(new char[size]);
    if (fread(buf.get(), 1, size, f) != (size_t)size) {
        perror("fread");
        return { };
    }
    std::string result(buf.get(), size);
    return result;
}

bool JQGuetzli_WriteFile(FILE* f, const std::string& contents) {
    if (fwrite(contents.data(), 1, contents.size(), f) != contents.size()) {
        perror("fwrite");
        return false;
    }
    if (fclose(f) < 0) {
        perror("fclose");
        return false;
    }

    return true;
}

JQGuetzli::ProcessResult JQGuetzli::process(const QString &inputImageFilePath, const QString &outputImageFilePath)
{
    QElapsedTimer timer;
    timer.start();

    ProcessResult result;

    result.originalSize = QFileInfo( inputImageFilePath ).size();

    std::unique_ptr<FILE, decltype(&fclose)> fin(
                fopen(inputImageFilePath.toLocal8Bit().data(), "rb"),
                fclose );
    if (!fin) {
        fprintf(stderr, "Can't open input file\n");
        return result;
    }

    std::string in_data = JQGuetzli_ReadFile(fin.get());
    std::string out_data;

    if ( in_data.empty() )
    {
        return result;
    }

    guetzli::Params params;
    params.butteraugli_target =
            guetzli::ButteraugliScoreForQuality(quality);

    guetzli::ProcessStats stats;

    if (verbose) {
        stats.debug_output_file = stdout;
    }

    static const unsigned char kJpegMagicBytes[] = {
        0xFF, 0xD8,
    };
    if (in_data.size() < 2 ||
            memcmp(in_data.data(), kJpegMagicBytes, sizeof(kJpegMagicBytes)) != 0) {
        fprintf(stderr, "Only JPEG input is supported\n");
        return result;
    }

    if (!guetzli::Process(params, &stats, in_data, &out_data)) {
        fprintf(stderr, "Guetzli processing failed\n");
        return result;
    }

    FILE* fout = fopen(outputImageFilePath.toLocal8Bit().data(), "wb");
    if (!fout) {
        fprintf(stderr, "Can't open output file for writing\n");
        return result;
    }

    if ( !JQGuetzli_WriteFile(fout, out_data) )
    {
        return result;
    }

    result.processSucceed = true;
    result.resultSize = QFileInfo( outputImageFilePath ).size();
    result.compressionRatio = (double)result.resultSize / (double)result.originalSize;
    result.timeConsuming = timer.elapsed();

    return result;
}
