#ifndef WINZIPEXTRACTOR_H
#define WINZIPEXTRACTOR_H

#include "zipextractor.h"

class Zip7zExtractor : public ZipExtractor
{

public:

   bool     unzip(QString zipFile , QString outputFolder , bool overwrite);

};

#endif // WINZIPEXTRACTOR_H
