/*********************************************************
 * Copyright (C) 2020, Val Doroshchuk <valbok@gmail.com> *
 *                                                       *
 * This file is part of QtAVPlayer.                      *
 * Free Qt Media Player based on FFmpeg.                 *
 *********************************************************/

#ifndef QAVFVIDEORAME_H
#define QAVFVIDEORAME_H

#include <QtAVPlayer/qavframe.h>
#include <QVariant>
#ifndef QT_NO_MULTIMEDIA
#include <QVideoFrame>
#endif

extern "C" {
#include <libavutil/frame.h>
}

QT_BEGIN_NAMESPACE

class QAVVideoFramePrivate;
class QAVCodec;
class Q_AVPLAYER_EXPORT QAVVideoFrame : public QAVFrame
{
public:
    enum HandleType
    {
        NoHandle,
        GLTextureHandle,
        MTLTextureHandle
    };

    QAVVideoFrame();
    QAVVideoFrame(const QAVFrame &other);
    QAVVideoFrame(const QAVVideoFrame &other);
    QAVVideoFrame(const QSize &size, AVPixelFormat fmt);

    QAVVideoFrame &operator=(const QAVFrame &other);
    QAVVideoFrame &operator=(const QAVVideoFrame &other);

    QSize size() const;

    struct MapData
    {
        int size = 0;
        int bytesPerLine[4] = {0};
        uchar *data[4] = {nullptr};
        AVPixelFormat format = AV_PIX_FMT_NONE;
    };

    MapData map() const;
    HandleType handleType() const;
    QVariant handle() const;

    AVPixelFormat format() const;
    QString formatName() const;
    QAVVideoFrame convertTo(AVPixelFormat fmt) const;
#ifndef QT_NO_MULTIMEDIA
    operator QVideoFrame() const;
#endif

protected:
    Q_DECLARE_PRIVATE(QAVVideoFrame)
};

Q_DECLARE_METATYPE(QAVVideoFrame)
Q_DECLARE_METATYPE(AVPixelFormat)

QT_END_NAMESPACE

#endif
