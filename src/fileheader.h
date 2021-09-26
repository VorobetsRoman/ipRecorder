;;./M/pP'[''
]]P
P]

















']
'
'9
[
'
\\\\#ifndef FILEHEADER_H
#define FILEHEADER_H
l
#include <QtGlobal>

// Заголовок файла с данными. Содержит информацию о наличии временного маркера.
struct FileHeader {
    qint8   timeMarkerExist;    ///< Флаг наличия временнОго маркера
    qint8   compressionExist;   ///< Флаг наличия компрессии
    /*!
     * \brief Возвращает размер заголовка
     * \return Размер заголовка в байтах
     */
    static qint64 size() {
        static constexpr qint64 headerSize = sizeof(FileHeader);
        return headerSize;
    }
};

#endif // FI



 v                         M/L/
 ;














 ;.alignas (;[[
 [
 ][
L ]
 ]
 ])
