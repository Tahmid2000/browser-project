/*
 * browserSupport.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#include "browserSupport.h"

#include <string>

//default constructor, sets valid to false
url::url()
: urlValid(false)
{
    
}

//overloaded constructor
url::url(const std::string &urlText)
: urlText(urlText), urlValid(true)
{
    
}

//sets new text
void url::text(const std::string &urlText)
{
    this->urlText = urlText;
}

//return text
std::string url::text() const
{
    return urlText;
}

//returns validity
bool url::valid() const
{
    return urlValid;
}

//returns text
url::operator std::string() const
{
	return text();
}

//operator<< using ostream
std::ostream& operator<<(std::ostream &out, const url &other)
{
    out << other.text();
    return out;
}

std::vector<url> *browserSupport::pVector = nullptr;
//static function for traverse used in history method
void browserSupport::buildHistory(const url &nextURL)
{
	if (pVector != nullptr)
	{
		(*pVector).push_back(nextURL);
	}
}

//traverses the history
std::size_t browserSupport::history(std::vector<url> &historyURLs)
{
	historyURLs.clear();
	browserSupport::pVector = &historyURLs;

	historyQueue.traverse(&browserSupport::buildHistory);


	browserSupport::pVector = nullptr;

	return 0;
}
 
//default constructor that sets the max and uses default constructor for currentURL
browserSupport::browserSupport()
    : theMax(50), currentURL()
{
    
}

//goes to the back of the cache, backStack
url browserSupport::back()
{
    //checks if backStack is empty
    if(backStack.empty() == false)
    {
        //if the url is valid, it gets pushed to frontStack
        if(currentURL.valid() == true)
        {
            forwardStack.push(currentURL);
        }
        //if the top of backStack is valid, it is set to the currentURL
        if(backStack.top().valid() == true)
            currentURL = backStack.top();
        backStack.pop();
    }
    return currentURL;
}

//goes to the front of the cache, forwardStack
url browserSupport::forward()
{
    //checks if forwardStack is empty
    if(forwardStack.empty() == false)
    {
        //if the url is valid, it gets pushed to the backStack
        if(currentURL.valid() == true)
        {
            backStack.push(currentURL);
        }
        //if the top of forwardStack is valid, it is set to currentURL
        if(forwardStack.top().valid() == true)
            currentURL = forwardStack.top();
        forwardStack.pop();
    }
    return currentURL;
}

void browserSupport::display(const url &newURL)
{
    //if the currentURL is valid, its get pushed to the backStack
    if(currentURL.valid() == true)
    {
        backStack.push(currentURL);
    }
    //sets specified url to currentURL
    currentURL = newURL;
    //if the historyQueue is empty, the new url is added to it without other checkin g
    if(historyQueue.empty() == true)
    {
        historyQueue.push(newURL);
    }
    //if it is not empty and the new url isn't the same as the most recently added to queue,
    //it is pushed to the url
    else if(historyQueue.empty() == false && currentURL != historyQueue.back())
    {
       historyQueue.push(newURL);
    }
    //if the size is more than the max, it is popped until it is max
    if(historyQueue.size() > theMax)
    {
        while(historyQueue.size() > theMax)
        {
            historyQueue.pop();
        }
    }
    //clears out theForward stack since their is a new url
    forwardStack.clear();
}
  
//clears historyQueue and returns its size
std::size_t browserSupport::clearHistory()
{
    std::size_t temp = historyQueue.size();
    historyQueue.clear();
    return temp;
}
    
//sets currentURL back to default, backStack, and forwardStack and returns the sum of their sizes
std::size_t browserSupport::clearCache()
{
    std::size_t temp3 = 0;
    std::size_t temp1 = backStack.size();
    std::size_t temp2 = forwardStack.size();
    if(currentURL.valid() == true)
        temp3 = 1;
    currentURL = url();
    backStack.clear();
    forwardStack.clear();
    return temp1 + temp2 + temp3;
}

//return the max size
std::size_t browserSupport::maximum() const
{
    return theMax;
}

//changes the max size and readjusts the historyQueue to match the new size
void browserSupport::maximum(std::size_t newMax)
{
    theMax = newMax;
    while(historyQueue.size() > theMax)
    {
        historyQueue.pop();
    }
}
    
