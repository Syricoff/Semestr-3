#include "BMP/BMP.h"
#include "FileLogging/FileLogging.h"

int main(int argc, char *argv[])
{
    std::string bmp_file{};
    std::string new_bmp_file{};
    std::string error_file{"error_log.txt"};
    if (argc == 2)
    {
        bmp_file = new_bmp_file = argv[1];
    }
    else if (argc == 3)
    {
        bmp_file = argv[1];
        new_bmp_file = argv[2];
    }
    else if (argc == 4)
    {
        bmp_file = argv[1];
        new_bmp_file = argv[2];
        error_file = argv[3];
    }
    FileLogging error_log(error_file);
    try
    {
        BMP bmp(bmp_file);
        bmp.adjustColorIntensity(0.7f); // Увеличение насыщенности
        bmp.save(new_bmp_file);
    }
    catch (const std::exception &e)
    {
        error_log.Logging(e.what());
    }
    return 0;
}