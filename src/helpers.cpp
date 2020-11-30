#include "helpers.h"
#include "fmt/format.h"

using namespace std;

string fmtSize(size_t size)
{
    if (size < 1024) return fmt::format("{:>} B ", size);

    double sd = size / 1024.0;
    if (sd < 1024.0) return fmt::format("{:>.4g} kB", sd);

    sd /= 1024.0;
    if (sd < 1024.0) return fmt::format("{:>.4g} MB", sd);

    sd /= 1024.0;
    return fmt::format("{:>.4g} GB", sd);
}

string fmtPerc(double p)
{
    return fmt::format("{:>.1f}%",p);
}