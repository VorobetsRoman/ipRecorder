#ifndef FILEHEADER_H
#define FILEHEADER_H

#include <QtGlobal>

// Заголовок файла с данными. Содержит информацию о наличии временного маркера.
struct FileHeader {
    qint8   timeMarkerExist;
    qint8   compressionExist;
    static qint64 size() {
        static constexpr qint64 headerSize = sizeof(FileHeader);
        return headerSize;
    }
};

#endif // FILEHEADER_H
