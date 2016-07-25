#include "cttempfile.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

CtTempFile::CtTempFile(const std::string & filePath)
    : path(filePath)
{

}

const std::string & CtTempFile::filePath() const
{
    return path;
}

bool CtTempFile::create(int size)
{
    fd = mkostemp((char*)path.c_str(), O_CLOEXEC);
    if (fd == -1) {
        msg = strerror(errno);
        fprintf(stderr, "Can't open file %s: %m\n", path.c_str());
        return false;
    }
    if (ftruncate(fd, size) == -1) {
        ::close(fd);
        msg = strerror(errno);
        fprintf(stderr, "Can't open file %s: %m\n", path.c_str());
        return false;
    }
    unlink(path.c_str());
    return true;
}

void CtTempFile::close()
{
    ::close(fd);
}

int CtTempFile::descriptor() const
{
    return fd;
}

std::string CtTempFile::errorMessage() const
{
    return msg;
}
