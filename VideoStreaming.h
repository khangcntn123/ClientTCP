#pragma once

#include <QObject>

class VideoStreaming  : public QObject
{
	Q_OBJECT

public:
	VideoStreaming(QObject *parent);
	~VideoStreaming();
};
