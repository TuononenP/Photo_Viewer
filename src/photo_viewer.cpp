/*********************************************************
 * Author: Petri Tuononen
 * Date started: 30/04/2010
 * Info: Made for University of Portsmouth's Group Design
 * 		 Project course. The aim is to display images like
 * 		 photo frames or similar multimedia devices.
 *
 * App features:
 * 		-pressing 1/4 of window's left side shows
 * 		 previous picture
 * 		-pressing 1/4 of window's right side shows
 * 		 next picture
 * 		-pressing window's middle section
 * 		 starts/stops slide show
 ********************************************************/
#include "photo_viewer.h"

/**
 * Constructor
 */
Photo_Viewer::Photo_Viewer(QWidget *parent)
    : QMainWindow(parent)
{
	//define path for image files
	setImgPath("./images/");
	//define filetype
	setFiletypeFilter("jpg");
	//populate string vector list with jpg file names
	getSpecificFilesFromDir(getFiletypeFilter(), files);
	//at the start the img location is 0
	setImgLoc(0);
	//set default speed for slideshow
	setSlideshowSpeed(2000);
	//set slideshow toggle off
	setSlideshowToggle(0);

	//setup user interface
	ui.setupUi(this);
	//set screen size
	setSize(888, 600);
//	setSize(888, 500);
	this->resize(maxWidth, maxHeight);
	//center screen
	centerScreen();
	//creates a QLabel which parent is QMainWindow.
	createImageLabel();
}

/**
 * Destructor
 */
Photo_Viewer::~Photo_Viewer()
{
}

/**
 * Get an amount of files with specified file
 * type in the directory.
 */
int Photo_Viewer::getDirFileAmount()
{
	return files.size();
}

/**
 * Set the location of the image on img vector.
 */
void Photo_Viewer::setImgLoc(unsigned int loc)
{
	imgLoc = loc;
}

/**
 * Get the location of the image on img vector.
 */
unsigned int Photo_Viewer::getImgLoc()
{
	return imgLoc;
}

/**
 * Set the interval (in ms) for image change speed in slideshow.
 */
void Photo_Viewer::setSlideshowSpeed(int ms)
{
	slideshowSpeed = ms;
}

/**
 * Get the rate which images are changed in slideshow.
 */
int Photo_Viewer::getSlideshowSpeed()
{
	return slideshowSpeed;
}

/**
 * Set the file type filter.
 */
void Photo_Viewer::setFiletypeFilter(string filter)
{
	filetype = filter;
}

/**
 * Get the file type filter.
 */
string Photo_Viewer::getFiletypeFilter()
{
	return filetype;
}

/**
 * Set image directory path.
 */
void Photo_Viewer::setImgPath(const char* path) {
	imgPath = path;
}

/**
 * Get image directory path.
 */
const char* Photo_Viewer::getImgPath()
{
	return imgPath;
}

/**
 * Set slideshow on/off.
 */
void Photo_Viewer::setSlideshowToggle(int toggle)
{
	slideshowToggle = toggle;
}

/**
 *	Get the status of slideshow toggle.
 */
int Photo_Viewer::getSlideshowToggle()
{
	return slideshowToggle;
}

/**
 * Creates an image label that fills QMainWindow and reloads the first
 * image and scales it to the size of the label.
 */
void Photo_Viewer::createImageLabel()
{
	imgLbl = new QLabel(this);
	imgLbl->setBackgroundRole(QPalette::Base);
	imgLbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	//using dynamic memory
	char* filename;
	//get the current image location
	string str = files.at(getImgLoc());
	filename = new char[str.length() + 1];
	//copy string to char
	strcpy(filename, str.c_str());
	//change image
	setNewImage(filename);
	//free up memory
	delete[] filename;
    imgLbl->resize(maxWidth, maxHeight);
    imgLbl->setScaledContents(TRUE);
    imgLbl->show();
}

/**
 * Sets the size of the main window.
 */
void Photo_Viewer::setSize(int width, int height)
{
	maxWidth = width;
	maxHeight = height;
}


/**
 * Defines mouse button press event.
 */
void Photo_Viewer::mousePressEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	slideTimer.stop();
}

/**
 * Defines mouse button release event.
 */
void Photo_Viewer::mouseReleaseEvent(QMouseEvent *pEvent)
{
	//if left mouse button pressed
	if (pEvent->button() == Qt::LeftButton)
	{
		int sizeX = pEvent->x();
		//previous button pressed
		if (sizeX<=222) {
			previousImage();
		}
		//next button pressed
		if (sizeX>=666) {
			nextImage();
		}
		//middle section pressed
		if (sizeX>222 && sizeX<666) {
			//invert slideshow toggle
			if (getSlideshowToggle()==0) {
				setSlideshowToggle(1);
			} else {
				setSlideshowToggle(0);
			}
			if (getSlideshowToggle()==1) {
				startSlideshow();
			}
		}
	}
}

/**
 * Sets a new image to image label.
 */
void Photo_Viewer::setNewImage(char* filename)
{
	string fn = filename;
	string imgP = getImgPath();
	//append image path and filename
	string fullP = imgP+fn;
	//convert string to char array
	char *fullPath = (char*)fullP.c_str();
	QPixmap image(fullPath);
	imgLbl->setPixmap(image);
}

/**
 * Sets previous image to image label.
 */
void Photo_Viewer::previousImage()
{
	//using dynamic memory
	char* filename;
	//check if a previous image exists
	if (getImgLoc()>0) {
		//current image location - 1
		string str = files.at(getImgLoc() - 1);
		filename = new char[str.length() + 1];
		//copy string to char
		strcpy(filename, str.c_str());
		//change image
		setNewImage(filename);
		//free up memory
		delete[] filename;
		//set new image location to be one number lower
		setImgLoc(getImgLoc() - 1);
	} else { //get the last image
		string str = files.at(files.size() - 1);
		filename = new char[str.length() + 1];
		//copy string to char
		strcpy(filename, str.c_str());
		//change image
		setNewImage(filename);
		//free up memory
		delete[] filename;
		//set image location to last image
		setImgLoc(files.size() - 1);
	}
}

/**
 * Sets next image to image label.
 */
void Photo_Viewer::nextImage()
{
	//using dynamic memory
	char* filename;
	//check if a next image exists
	if (getImgLoc()<files.size()-1) {
		//current image location + 1
		string str = files.at(getImgLoc() + 1);
		filename = new char[str.length() + 1];
		//copy string to char
		strcpy(filename, str.c_str());
		//change image
		setNewImage(filename);
		//free up memory
		delete[] filename;
		//set new image location to be one number higher
		setImgLoc(getImgLoc() + 1);
	}else { //get the first image
		string str = files.at(0);
		filename = new char[str.length() + 1];
		//copy string to char
		strcpy(filename, str.c_str());
		//change image
		setNewImage(filename);
		//free up memory
		delete[] filename;
		//set image location to first image
		setImgLoc(0);
	}
}

/**
 * Centers application window location to the center
 * of the physical screen size
 */
void Photo_Viewer::centerScreen()
{
	QDesktopWidget *desktop = QApplication::desktop();

	int screenWidth, width;
	int screenHeight, height;
	int x, y;
	QSize windowSize;

	//get width and height of screen
	screenWidth = desktop->width();
	screenHeight = desktop->height();

	//size of the application window
	windowSize = size();
	width = windowSize.width();
	height = windowSize.height();

	//computations
	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;
	y -= 50;

	//move window to desired coordinates
	move(x, y);
}

/**
 * Adds filenames ending with specified filetype to a vector.
 */
int Photo_Viewer::getSpecificFilesFromDir(string ftype, vector<string> &files)
{
	//define folder to scan for files
	string dir = string(getImgPath());
	//create vector of strings to hold all filenames
	vector<string> allFiles = vector<string>();

	//get all files from folder
	getDir(dir, allFiles);

	//loop through all filenames to search for filenames which
	for(unsigned int i = 0; i<allFiles.size(); i++) {
		//get file name
		string fname = allFiles[i];
		//get char length
		int length = fname.size();
		//if string contains at least 3 charachers
		if (length>=3) {
			//get last three characters
			string subStr = fname.substr(length-3);
			//if last three characters are jpg
			if(subStr==ftype) {
				//add filename to specific filenames vector
				files.push_back(allFiles[i]);
			}
		}
	}
	//sort files  to ascending order
	sort(files.begin(), files.end());
	return 0;
}

/**
 * Get all file names in a specified directory.
 */
int Photo_Viewer::getDir(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

/**
 * Prints all files with a type of JPG.
 */
void Photo_Viewer::printJpgFilesFromDir()
{
	string ftype = "jpg";
	//create vector to hold specific filenames
	vector<string> files = vector<string>();
	//get all filenames with specified filetype
	getSpecificFilesFromDir(ftype, files);

	for(unsigned int i = 0; i<files.size(); i++) {
		cout << files[i] << endl;
	}
}

/**
 * Defines what happens after every timer interval
 */
void Photo_Viewer::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    nextImage();
    update();
}

/**
 * Starts the slideshow.
 */
void Photo_Viewer::startSlideshow()
{
	slideTimer.start(getSlideshowSpeed(), this);
	nextImage();
	update();
}
