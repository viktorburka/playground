#ifndef CTTEMPFILE_H
#define CTTEMPFILE_H

#include <string>


class CtTempFile
{
public:
    CtTempFile(const std::string & filePath);

    const std::string & filePath() const;
    int descriptor() const;
    std::string errorMessage() const;

    bool create(int size);
    void close();

private:
    std::string path;
    std::string msg;
    int fd;
};

#endif // CTTEMPFILE_H
