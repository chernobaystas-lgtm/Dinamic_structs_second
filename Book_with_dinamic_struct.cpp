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
	
	Chapter() : pages(0), number_of_chapter(0.0), title_of_chapter("No title"), epigraph("No epigraph") {
		cout << "[Chapter] Default constructor: " << title_of_chapter << endl;
	}

	Chapter(string title,  string epigraph, int pages, double number) : pages(pages), number_of_chapter(number), title_of_chapter(title), epigraph(epigraph) { 
		cout << "[Chapter] Constructor: " << title_of_chapter << endl; 
	
	}

	~Chapter() {
		cout << "[Chapter] Destructor: " << title_of_chapter << endl;
	}

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

	int get_pages() const { return pages; }
	double  get_number_of_chapter() const { return number_of_chapter; }
	string get_title_of_chapter() const { return title_of_chapter; }
	string get_epigraph() const { return epigraph; }

	
	void set_pages(int p) { pages = p; }
	void set_number_of_chapter(double number) { number_of_chapter = number; }
	void set_title_of_chapter(string title) { title_of_chapter = title; }
	void set_epigraph(string ep) { epigraph = ep; }

};

class Book {

private:
	string title_of_book;
	string genre;
	string author;
	Chapter* chapters;
	int chapter_count{ 0 };



public:
	Book() : title_of_book("No title"), genre("No genre"), author("No author"), chapters(nullptr), chapter_count(0) {
		cout << "[Book] Default constructor: " << title_of_book << endl;
	}
	Book(string title, string genre, string auth) : title_of_book(title), genre(genre), author(auth), chapters(nullptr), chapter_count(0) {
	
		cout << "[Book] Constructor (no chapters): " << title_of_book << endl;
	}

	Book(const Book& other) : title_of_book(other.title_of_book), genre(other.genre), author(other.author), chapters(nullptr), chapter_count(other.chapter_count) {
		cout << "[Book] Copy constructor: " << title_of_book << endl;
		if (other.chapters) {
			chapters = new Chapter[chapter_count];
			for (int i = 0; i < chapter_count; i++) {
				chapters[i] = other.chapters[i];
			}
		}
	}

	Book(string title, string bookGenre, string author, int count) : title_of_book(title), genre(bookGenre), author(author), chapter_count(count) {
		cout << "[Book] Constructor: " << title_of_book << " creating " << chapter_count << " chapters..." << endl;
		chapters = new Chapter[chapter_count];
		for (int i = 0; i < chapter_count; i++) {
			cout << "Enter data for chapter " << i + 1 << ":" << endl;
			chapters[i].input();
		}
	}

	Book& operator=(const Book& other) {
		if (this == &other) return *this;
		title_of_book = other.title_of_book;
		genre = other.genre;
		author = other.author;
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

	Book(Book&& other) noexcept : title_of_book(std::move(other.title_of_book)), genre(std::move(other.genre)), author(std::move(other.author)), chapters(other.chapters), chapter_count(other.chapter_count) {
		other.chapters = nullptr;
		other.chapter_count = 0;
	}


	~Book() {
		cout << "[Book] Destructor: " << title_of_book << " (destroying its chapters now)" << endl;
		for (int i = 0; i < chapter_count; i++) {
			chapters[i].~Chapter();
		}
		
	}




	void show_book()  {
		cout << "Title of book: " << title_of_book << endl;
		cout << "Genre: " << genre << endl;
		cout << "Author: " << author << endl;
		cout << "Number of chapters: " << chapter_count << endl;
		for (int i = 0; i < chapter_count; i++) {
			cout << "--- Chapter " << i + 1 << " ---" << endl;
			chapters[i].show_chapter();
		}
		cout << "Total pages: " << total_pages() << endl;
	}

	double total_pages()  {
		double sum = 0;
		for (int i = 0; i < chapter_count; i++) {
			sum += chapters[i].get_pages();
		}
		return sum;
	}

	string get_title_of_book() const {
		return title_of_book;
	}

	string get_genre() const {
		return genre;
	}

	string get_author() const {
		return author;
	}

	int get_chapter_count() const {
		return chapter_count;
	}


	void set_title_of_book(string title) {
		title_of_book = title;
	}

	void set_genre(string new_genre) {
		genre = new_genre;
	}

	void set_author(string new_author) {
		author = new_author;
	}

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	cout << "===== CREATE BOOK =====" << endl;

	Book book("Harry Potter", "Fantasy", "J.K. Rowling", 2);

	cout << "\n===== BOOK INFORMATION =====" << endl;

	book.show_book();

	cout << "\n===== END OF MAIN =====" << endl;

	return 0;
}
