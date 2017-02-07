#ifndef FILEHEADER_H
#define FILEHEADER_H

#include <QtGlobal>

// Заголовок файла с данными. Содержит информацию о наличии временного маркера.
struct FileHeader {
    qint16 timeMarkerExist;
};

#endif // FILEHEADER_H
