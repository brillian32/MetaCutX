//
// Created by 17305 on 2023/11/30.
//

#ifndef PLAYCONTROLLER_H
#define PLAYCONTROLLER_H
#include <QArgument>
#include "Singleton.h"
#include <QObject>
#include "DecodeVideo.h"

class PlayController : public QObject
{
	Q_OBJECT
	DECLARE_SINGLETON(PlayController)
public:
	PlayController();
	~PlayController() override;

	void setVideoDecoder(DecodeVideo *decoder);
signals:
	void sigFrameReady(cv::Mat frame);

public slots:
	void setCurrentFrame(int64 curFrame);
	void play();
	void pause();
	bool isPlaying();
	void nextFrame();
	void preFrame();
	int64 getFrameCount();

private:
	DecodeVideo *m_decoder;
	int64 m_curFrame = 0;
};


#endif //PLAYCONTROLLER_H
