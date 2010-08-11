#ifndef PHOTO_VIEWER_H
#define PHOTO_VIEWER_H

#include <QtGui/QMainWindow>
#include "ui_photo_viewer.h"
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QTimer>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <unistd.h> //unix sleep
#include <time.h>

using namespace std;

class Photo_Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Photo_Viewer(QWidget *parent = 0);
    ~Photo_Viewer();
    void setSize(int width, int height);
    void mouseReleaseEvent(QMouseEvent *pEvent);
    void mousePressEvent(QMouseEvent *event);
    void nextImage();
    void previousImage();
    void setNewImage(char*);
    void centerScreen();
    void createImageLabel();
    int getDir(string dir, vector<string> &files);
    int getSpecificFilesFromDir(string ftype, vector<string> &files);
    void printJpgFilesFromDir();
    int getDirFileAmount();
    unsigned int getImgLoc();
    void setImgLoc(unsigned int);
    void startSlideshow();
    void setSlideshowSpeed(int speed);
    int getSlideshowSpeed();
    void setFiletypeFilter(string);
    string getFiletypeFilter();
    void setImgPath(const char*);
    const char* getImgPath();
    void setSlideshowToggle(int);
    int getSlideshowToggle();
    void timerEvent(QTimerEvent* event);
    QBasicTimer slideTimer;

private:
    Ui::Photo_ViewerClass ui;
    QLabel *imgLbl;
    int maxWidth;
    int maxHeight;
    vector<string> files;
    unsigned int imgLoc;
    const char* imgPath;
    string filetype;
    int slideshowSpeed;
    int slideshowToggle;

};

#endif // PHOTO_VIEWER_H
