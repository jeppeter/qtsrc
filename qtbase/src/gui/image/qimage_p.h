/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QIMAGE_P_H
#define QIMAGE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

#include <QMap>
#include <QVector>

QT_BEGIN_NAMESPACE

class QImageWriter;

struct Q_GUI_EXPORT QImageData {        // internal image data
    QImageData();
    ~QImageData();
    static QImageData *create(const QSize &size, QImage::Format format);
    static QImageData *create(uchar *data, int w, int h,  int bpl, QImage::Format format, bool readOnly, QImageCleanupFunction cleanupFunction = 0, void *cleanupInfo = 0);

    QAtomicInt ref;

    int width;
    int height;
    int depth;
    int nbytes;               // number of bytes data
    qreal devicePixelRatio;
    QVector<QRgb> colortable;
    uchar *data;
    QImage::Format format;
    int bytes_per_line;
    int ser_no;               // serial number
    int detach_no;

    qreal  dpmx;                // dots per meter X (or 0)
    qreal  dpmy;                // dots per meter Y (or 0)
    QPoint  offset;           // offset in pixels

    uint own_data : 1;
    uint ro_data : 1;
    uint has_alpha_clut : 1;
    uint is_cached : 1;
    uint is_locked : 1;

    QImageCleanupFunction cleanupFunction;
    void* cleanupInfo;

    bool checkForAlphaPixels() const;

    // Convert the image in-place, minimizing memory reallocation
    // Return false if the conversion cannot be done in-place.
    bool convertInPlace(QImage::Format newFormat, Qt::ImageConversionFlags);

    QMap<QString, QString> text;

    bool doImageIO(const QImage *image, QImageWriter* io, int quality) const;

    QPaintEngine *paintEngine;
};

typedef void (*Image_Converter)(QImageData *dest, const QImageData *src, Qt::ImageConversionFlags);
typedef bool (*InPlace_Image_Converter)(QImageData *data, Qt::ImageConversionFlags);

extern Image_Converter qimage_converter_map[QImage::NImageFormats][QImage::NImageFormats];
extern InPlace_Image_Converter qimage_inplace_converter_map[QImage::NImageFormats][QImage::NImageFormats];

void convert_generic(QImageData *dest, const QImageData *src, Qt::ImageConversionFlags);
bool convert_generic_inplace(QImageData *data, QImage::Format dst_format, Qt::ImageConversionFlags);

void dither_to_Mono(QImageData *dst, const QImageData *src, Qt::ImageConversionFlags flags, bool fromalpha);

const uchar *qt_get_bitflip_array();
Q_GUI_EXPORT void qGamma_correct_back_to_linear_cs(QImage *image);

#if defined(_M_ARM) // QTBUG-42038
#pragma optimize("", off)
#endif
inline int qt_depthForFormat(QImage::Format format)
{
    int depth = 0;
    switch(format) {
    case QImage::Format_Invalid:
    case QImage::NImageFormats:
        Q_UNREACHABLE();
    case QImage::Format_Mono:
    case QImage::Format_MonoLSB:
        depth = 1;
        break;
    case QImage::Format_Indexed8:
    case QImage::Format_Alpha8:
    case QImage::Format_Grayscale8:
        depth = 8;
        break;
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    case QImage::Format_RGBX8888:
    case QImage::Format_RGBA8888:
    case QImage::Format_RGBA8888_Premultiplied:
    case QImage::Format_BGR30:
    case QImage::Format_A2BGR30_Premultiplied:
    case QImage::Format_RGB30:
    case QImage::Format_A2RGB30_Premultiplied:
        depth = 32;
        break;
    case QImage::Format_RGB555:
    case QImage::Format_RGB16:
    case QImage::Format_RGB444:
    case QImage::Format_ARGB4444_Premultiplied:
        depth = 16;
        break;
    case QImage::Format_RGB666:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_ARGB8565_Premultiplied:
    case QImage::Format_ARGB8555_Premultiplied:
    case QImage::Format_RGB888:
        depth = 24;
        break;
    }
    return depth;
}

#if defined(_M_ARM)
#pragma optimize("", on)
#endif

inline QImage::Format qt_alphaVersion(QImage::Format format)
{
    switch (format) {
    case QImage::Format_RGB16:
        return QImage::Format_ARGB8565_Premultiplied;
    case QImage::Format_RGB555:
        return QImage::Format_ARGB8555_Premultiplied;
    case QImage::Format_RGB666:
        return QImage::Format_ARGB6666_Premultiplied;
    case QImage::Format_RGB444:
        return QImage::Format_ARGB4444_Premultiplied;
    case QImage::Format_RGBX8888:
        return QImage::Format_RGBA8888_Premultiplied;
    case QImage::Format_BGR30:
        return QImage::Format_A2BGR30_Premultiplied;
    case QImage::Format_RGB30:
        return QImage::Format_A2RGB30_Premultiplied;
    default:
        break;
    }
    return QImage::Format_ARGB32_Premultiplied;
}

inline QImage::Format qt_maybeAlphaVersionWithSameDepth(QImage::Format format)
{
    const QImage::Format toFormat = qt_alphaVersion(format);
    return qt_depthForFormat(format) == qt_depthForFormat(toFormat) ? toFormat : format;
}

inline QImage::Format qt_alphaVersionForPainting(QImage::Format format)
{
    QImage::Format toFormat = qt_alphaVersion(format);
#if defined(__ARM_NEON__) || defined(__SSE2__)
    // If we are switching depth anyway and we have optimized ARGB32PM routines, upgrade to that.
    if (qt_depthForFormat(format) != qt_depthForFormat(toFormat))
        toFormat = QImage::Format_ARGB32_Premultiplied;
#endif
    return toFormat;
}

QT_END_NAMESPACE

#endif // QIMAGE_P_H
