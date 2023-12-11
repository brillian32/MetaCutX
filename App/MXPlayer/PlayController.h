//
// Created by 17305 on 2023/11/30.
//

#ifndef PLAYCONTROLLER_H
#define PLAYCONTROLLER_H
#include "DecodeVideo.h"
#include "Singleton.h"

#include <QArgument>
#include <QObject>
#include <QThreadPool>

class PlayController : public QObject
{
	Q_OBJECT
	DECLARE_SINGLETON(PlayController)
public:
	PlayController();
	~PlayController() override;

	void setVideoDecoder(DecodeVideo *decoder);
signals:
	void sigFrameReady(cv::Mat frame,int64 curFrame);

public slots:
	void setCurrentFrame(int64 curFrame);
	void play();
	void pause();
	bool isPlaying();
	void nextFrame();
	void preFrame();
	int64 getFrameCount();

private:
	QThreadPool m_threadPool;
	DecodeVideo *m_decoder;
	int64 m_curFrame = 0;
};


#endif //PLAYCONTROLLER_H
