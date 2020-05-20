/*
 * browserSupport.h
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#ifndef BROWSERSUPPORT_H_
#define BROWSERSUPPORT_H_

#include <string>
#include <vector>

#include "stack.h"
#include "queue.h"

class url
{
	private:
        //members that are the actual url and if its a valid url
		std::string urlText;
		bool urlValid;
	public:
        //default constructor
        url();
        //overloaded constructor
		url(const std::string &urlText);
        //destrcutor
		virtual ~url()
        {
        }
        //change text
		void text(const std::string &urlText);
        //returns the string url
		std::string text() const;
        //returns whethe the url is valid or not
		bool valid() const;
        //overloaded operators
        bool operator<(const url& rhs) const { return urlText < rhs.urlText; }
        bool operator==(const url& rhs) const { return urlText == rhs.urlText; }

        operator std::string() const; // this allow us to do the following:
        //url myURL("utdallas.edu");
        //std::string text = static_cast<std::string>(myURL);
        //other overloaded operators
		bool operator> (const url& rhs) const { return rhs < *this; }
		bool operator<=(const url& rhs) const { return !(*this > rhs); }
		bool operator>=(const url& rhs) const { return !(*this < rhs); }
		bool operator!=(const url& rhs) const { return !(*this == rhs); }
};

std::ostream& operator<<(std::ostream &out, const url &other);

class browserSupport
{
	private:
        //this is needed for displaying the histroy
		static std::vector<url> *pVector;
        //queue of all the urls
        queue<url> historyQueue;
        //backStack of all previous urls, aka cache
        stack<url> backStack;
        //forwardStack of all previous urls, aka cache
        stack<url> forwardStack;
        //the actual url being added
        url currentURL;
        //the maximum size historyQueue can be
        std::size_t theMax;

	public:
        //constructor
		browserSupport();
        //desctructor
		virtual ~browserSupport()
        {
        }
        //goes to the back of the cache, backStack
		url back();
        //goes to the front of the cache, forwardStack
		url forward();
        //adds urls to history queue and displays the full history
		void display(const url &newURL);
        //clears historyQueue
		std::size_t clearHistory();
        //clears both stacks and sets url to default
		std::size_t clearCache();
        //gets theMax of historyQueue
		std::size_t maximum() const;
        //changes the maxium and adjusts the queue to match the size
		void maximum(std::size_t newMax);
        //traverse the history
		std::size_t history(std::vector<url> &historyURLs);
    
	private:
        //static function used by traverse
		static void buildHistory(const url &nextURL);
};

#endif /* BROWSERSUPPORT_H_ */
