#include "MoviePlayer.h"

// Function: Parameterized Constructor
// Purpose: Sets member variables to input, clears list, and calls loader
// Input: None
// Returns: Nothing
MoviePlayer::MoviePlayer(std::string filmName)
{
	mFilmName = filmName;
	mFilm.clear();
	currFrameNum = 0;
	loadTape();
}

// Function: Destructor
// Purpose: Empties the list
// Input: None
// Returns: Nothing
MoviePlayer::~MoviePlayer()
{
	mFilm.clear();
}

// Function: goFwrd
// Purpose: Moves the current "frame" forward by 1 frame
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::goFwrd()
{
	if (currFrameNum < getNumFrames())
	{
		currFrameNum++;
		mFilm.move_next();
	}
	else
	{
		return;
	}
}

// Function: goBack
// Purpose: Moves the current "frame" backward by 1 frame
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::goBack()
{
	if (currFrameNum > 0)
	{
		currFrameNum--;
		mFilm.move_prev();
	}
	else
	{
		return;
	}
}

// Function: rewind
// Purpose: Moves the current "frame" to the movie's beginning again
// Input: None
// Returns: Nothing
void MoviePlayer::rewind()
{
	currFrameNum = 0;
	mFilm.reset();
}

// Function: getCurrFrame
// Purpose: Gets the string that contains the current "frame" as stored
// in the list "mFilm"
// Input: None
// Returns: String with the current "frame"
std::string MoviePlayer::getCurrFrame()
{
    // TODO: Implement
	return mFilm.get_at_curr();
}

// Function: delCurrFrame
// Purpose: Deletes the current frame, moves forward to the next one
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::delCurrFrame()
{
	mFilm.remove_at_curr();
	currFrameNum--;
}

// Function: copyCurrFrame
// Purpose: Copies current frame and places the copy BEFORE the current frame
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::copyCurrFrame()
{
	mFilm.add_at_curr(mFilm.get_at_curr());
	currFrameNum++;
}

// Function: getCurrFrameNum
// Purpose: Gets the "index" that corresponds to the current frame
// Input: None
// Returns: Number of frames that have been viewed
unsigned MoviePlayer::getCurrFrameNum() const
{
	return currFrameNum;
}

// Function: getNumFrames
// Purpose: Gets the total number of frames in the movie
// Input: None
// Returns: The overall number of frames in the movie
unsigned int MoviePlayer::getNumFrames() const
{
	return mFilm.size();
}

// Function: getFrameSize
// Purpose: Gives the number of lines in a frame
// For how big the "screen" for the film should be
// Input: None
// Returns: The value stored in FRAMESIZE
unsigned int MoviePlayer::getFrameSize() const
{
	return FRAMESIZE;
}

// Function: getCurrFrame
// Purpose: Retrieves the current "frame" from the film list
// Modifies the inputted vector of GLabels to contain the current frame
// Input: A vector of "GLabels" that are the "screen" -- passed by reference
// Returns: Nothing
void MoviePlayer::getCurrFrame(Vector<GLabel*>& screen)
{
	if (currFrameNum != getNumFrames())
	{
		std::vector<std::string> frame;
		std::string temp = getCurrFrame();
		size_t index = temp.find_first_of('$');
		while (index != std::string::npos)
		{
			frame.push_back(temp.substr(0, index));
			temp = temp.substr(index + 1);
			index = temp.find_first_of('$');
		}
		frame.push_back(temp);
		for (int i = 0; i < screen.size(); i++)
		{
			if (frame[i].size() > 0)
			{
				if (frame[i].back() == '\\')
				{
					frame[i] += "\"";
				}
			}
			screen[i]->setLabel(frame[i]);
		}
		frame.clear();
	}
	else
	{
		return;
	}
}

// Function: loadTape
// Purpose: Uses mFilmName (set by constructor) to fill
// mFilm with strings that make up the movie to display
// Input: None
// Returns: Nothing
void MoviePlayer::loadTape()
{
	std::fstream fs(mFilmName, std::fstream::in | std::fstream::out);
	std::string line;
	std::string total;
	std::vector<std::string> frame;
	int repeat;
	while (!fs.eof())
	{
		for (int i = 0; i < 14; i++)
		{
			getline(fs, line);
			if (i > 0)
			{
				total += "$";
				total += line;
			}
			else
			{
				try 
				{
					repeat = std::stoi(line);
				}
				catch (std::exception& ex)
				{
					std::cout << "ERROR: " << ex.what() << '\n';
					std::cout << "\tUnable to convert \"" << line << "\" to a number.\n";
				}
			}
		}
		for (int i = 0; i < repeat; i++)
		{
			mFilm.insert_back(total);
		}
		total.clear();
	}
	mFilm.remove_back();
	fs.close();
}
