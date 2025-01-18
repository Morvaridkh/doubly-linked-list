#include <iostream>
using namespace std;

//Enter data

class songsNode
{
public:
	//Data in all of nodes(songs)
	string Song_name;
	string Artist_name;
	int Time;
	string Genre;
	songsNode* previous_song;
	songsNode* next_song;
	//Constructor
	songsNode(string song, string artist, int time, string genre) :
		Song_name(song), Artist_name(artist), Time(time), Genre(genre), previous_song(nullptr), next_song(nullptr) {}
};
class playlist
{
private:
	//where is the song?!
	songsNode* head;
	songsNode* tail;
public:
	playlist() :tail(nullptr), head(nullptr) {}
	void addSong(string Song_name, string Artist_name, int Time, string Genre);
	void display();
	void removeSongByName();
	void searchByName(string);
	//void searchByArtist_name(string);
	void search(const string& query);
	void sortSongByName(const string& field);
};
void playlist::addSong(string Song_name, string Artist_name, int Time, string Genre)
{
	songsNode* newSong = new songsNode(Song_name, Artist_name, Time, Genre);
	if (head)
	{
		tail->next_song = newSong;
		newSong->previous_song = tail;
		tail = newSong;
	}
	else
	{
		cout << "Add new song:"<<endl;
		head = tail = newSong;
	}
}

//delete ! think about it!
void playlist::removeSongByName()
{

}
void playlist::search(const string& query)
{
	songsNode* temp = head;
	while (temp)
	{
		if (temp->Song_name == query || temp->Artist_name == query || temp->Genre == query)
		{
			cout << "Found it! " << temp->Song_name << " by" << temp->Artist_name << endl;
		}
		temp = temp->next_song;
	}
}
void playlist::searchByName(string Song_name)
{
	songsNode* temp = head;
	bool find = false;
	while (temp)
	{
		if (temp->Song_name == Song_name)
		{
			cout << "Found it!!!" << temp->Song_name << ", Artist: " << temp->Artist_name 
				<<", Genre: " << temp->Genre << ", Time: " << temp->Time << " seconds" << endl;
			find = true;
		}
		temp = temp->next_song;
		if(find = false)
		{
			cout << "Can't found it!" << endl;
		}
	}
}
void playlist::sortSongByName(const string &field)
{
	//check the playlist that has a song or 1 song?
	if (!head || !head->next_song)
	{
		cout << "The playlist is empty or has 1 song!" << endl;
		return;
	}
	bool swapped;
	do {
		swapped = false;
		songsNode* current = head;
		while (current && current->next_song) {
			if ((field == "title" && current->Song_name > current->next_song->Song_name) ||
				(field == "artist" && current->Artist_name > current->next_song->Artist_name)) {
				swap(current, current->next_song);
				swapped = true;
			}
			current = current->next_song;
		}
	} while (swapped);

}
void playlist::display()
{
	if (!head)
	{
		cout << "The list is EMPTY!";
		return;
	}
	songsNode* current = head;
	while (current) 
	{
		cout << "Name: " << current->Song_name << endl;
		cout << "Artist: " << current->Artist_name << endl;
		cout << "Genre: " << current->Genre << endl;
		cout<<"Time: " << current->Time << " seconds" << endl;
		current = current->next_song;
	}
}

int main()
{
	playlist playlist;
	playlist.addSong("Dream", "Imagine Dragons", 258, "pop");
	playlist.addSong("The Lonely", "Christina ", 233, "pop");
	playlist.addSong("Symphony", "Beethoven", 334, "classic");
	playlist.addSong("Mirror", "Lil Wayne", 228, "rap");
	playlist.display();
	playlist.searchByName("Symphony");
	playlist.search("Lil Wayne");
	cout << "sort !!!!!" << endl;
	playlist.sortSongByName("Artist_name");
	playlist.display();
}