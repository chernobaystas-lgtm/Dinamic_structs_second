#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include  <cassert>
using namespace std;



class Chapter {

private:
	int pages{0};
	double number_of_chapter{ 0.0 };
	string title_of_chapter{"No title"};
	string epigraph{ "No epigraph" };
	
public:
	
	Chapter() : pages(0), number_of_chapter(0.0), title_of_chapter("No title"), epigraph("No epigraph") {}

	Chapter(string title,  string epigraph, int pages, double number) : pages(pages), number_of_chapter(number), title_of_chapter(title), epigraph(epigraph) {}
		
	Chapter(const Chapter& other) : pages(other.pages), number_of_chapter(other.number_of_chapter), title_of_chapter(other.title_of_chapter), epigraph(other.epigraph) {
	}

	Chapter& operator=(const Chapter& other) {
		if (this == &other) return *this;
		pages = other.pages;
		number_of_chapter = other.number_of_chapter;
		title_of_chapter = other.title_of_chapter;
		epigraph = other.epigraph;
		return *this;
	}

	~Chapter() {}

	void show_chapter() {
		cout << "Chapter number: " << number_of_chapter << endl;
		cout << "Title: " << title_of_chapter << endl;
		cout << "Pages: " << pages << endl;
		cout << "Epigraph: " << epigraph << endl;
	}

	void input() {
		cout << "Enter chapter number: ";
		cin >> number_of_chapter;
		cin.ignore();
		cout << "Enter title of chapter: ";
		getline(cin, title_of_chapter);
		cout << "Enter number of pages: ";
		cin >> pages;
		cin.ignore();
		cout << "Enter epigraph: ";
		getline(cin, epigraph);
	}


};

class Book : public Chapter {

private:
	string title_of_book;
	string genre;
	Chapter* chapters;
	int chapter_count{ 0 };



public:
	Book() : title_of_book("No title"), genre("No genre"), chapters(nullptr), chapter_count(0) {}
	Book(string title, string genre) : title_of_book(title), genre(genre), chapters(nullptr), chapter_count(0) {}

	Book(const Book& other) : title_of_book(other.title_of_book), genre(other.genre), chapters(nullptr), chapter_count(other.chapter_count) {
		if (other.chapters) {
			chapters = new Chapter[chapter_count];
			for (int i = 0; i < chapter_count; i++) {
				chapters[i] = other.chapters[i];
			}
		}
	}

	Book() : title_of_book("No title"), genre("No genre"), chapters(nullptr), chapter_count(0) {}
	Book(string title, string genre) : title_of_book(title), genre(genre), chapters(nullptr), chapter_count(0) {}

	Book(const Book& other) : title_of_book(other.title_of_book), genre(other.genre), chapters(nullptr), chapter_count(other.chapter_count) {
		if (other.chapters) {
			chapters = new Chapter[chapter_count];
			for (int i = 0; i < chapter_count; i++) {
				chapters[i] = other.chapters[i];
			}
		}
	}

	Book& operator=(const Book& other) {
		if (this == &other) return *this;
		title_of_book = other.title_of_book;
		genre = other.genre;
		chapter_count = other.chapter_count;
		if (chapters) {
			delete[] chapters;
		}
		chapters = nullptr;
		if (other.chapters) {
			chapters = new Chapter[chapter_count];
			for (int i = 0; i < chapter_count; i++) {
				chapters[i] = other.chapters[i];
			}
		}
		return *this;
	}

	~Book() {
		delete[] chapters;
	}


	Book& operator=(const Book& other) {
		if (this == &other) return *this;
		title_of_book = other.title_of_book;
		genre = other.genre;
		chapter_count = other.chapter_count;
		if (chapters) {
			delete[] chapters;
		}
		chapters = nullptr;
		if (other.chapters) {
			chapters = new Chapter[chapter_count];
			for (int i = 0; i < chapter_count; i++) {
				chapters[i] = other.chapters[i];
			}
		}
		return *this;
	}

	~Book() {
		delete[] chapters;
	}
};


int main()
{
    cout << "Hello World!\n";
}

