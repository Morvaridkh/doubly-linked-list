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
	void removeSongByName(const string&);
	void remove(const string&, const string&);
	void searchSongByName(string);
	void search(const string&);
	void swap(songsNode*,songsNode*);
	void shuffle();
	void moveDown(const string&);
	void moveUp(const string&);
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
		cout << "Add " << endl;
		head = tail = newSong;
	}
}
//delete by genre or artist or title
//first input we put the song name or specific artist name that we want to delete 
// or specific genre that we want to delete
//second input is just a key word that we use to find that specific options
void playlist::remove(const string& word, const string& specific)
{
	songsNode* temp = head;
	while (temp) {
		if ((specific == "N" && temp->Song_name == word) ||
			(specific == "A" && temp->Artist_name == word) ||
			(specific == "G" && temp->Genre == word))
		{
			if (temp == head)
			{
				head = temp->next_song;
			}
			if(temp == tail)
			{
				tail = temp->previous_song;
			}
			if (temp->previous_song)
			{
				temp->previous_song->next_song = temp->next_song;
			}
			if (temp->next_song)
			{
				temp->next_song->previous_song = temp->previous_song;
			}
			delete temp;
			break;
		}
		temp = temp->next_song;
	}
}
void playlist::removeSongByName(const string& name)
{
	songsNode* temp = head;
	while (temp)
	{
		if (temp->Song_name == name)
		{
			// 2 if is for update the pointer when we delete
			if (temp->previous_song)
			{
				temp->previous_song->next_song = temp->next_song;
			}
			if (temp->next_song)
			{
				temp->next_song->previous_song = temp->previous_song;
			}
			//if song to remove is the first in playlist
			if (temp == head)
			{
				head = temp->next_song;
			}
			//if song to remove is the last in playlist
			if (temp == tail)
			{
				tail = temp->previous_song;
			}
			delete temp;
			cout << "song name that we remove: " << name << endl;
			return;
		}
		temp = temp->next_song;
	}
}
//search by name or artist or genre
void playlist::search(const string& query)
{
	cout << "Search" << endl;
	songsNode* temp = head;
	while (temp)
	{
		if (temp->Song_name == query || temp->Artist_name == query || temp->Genre == query)
		{
			cout << "Found it! " << temp->Song_name << " by " << temp->Artist_name << " genre " << temp->Genre << endl;
		}
		temp = temp->next_song;
	}
}
//search by only name
void playlist::searchSongByName(string Song_name)
{
	songsNode* temp = head;
	//bool it's like flag 
	bool find = false;
	while (temp)
	{
		if (temp->Song_name == Song_name)
		{
			cout << "Found it!" << temp->Song_name << " Artist: " << temp->Artist_name
				<< " Genre: " << temp->Genre << " Time: " << temp->Time << " seconds" << endl;
			find = true;
		}
		temp = temp->next_song;
		if (find = false)
		{
			cout << "Can't found it!" << endl;
		}
	}
}
//swap function
void playlist::swap(songsNode* a, songsNode* b) {
	string tempTitle = a->Song_name;
	string tempArtist = a->Artist_name;
	string tempGenre = a->Genre;
	int tempDuration = a->Time;

	a->Song_name = b->Song_name;
	a->Artist_name = b->Artist_name;
	a->Genre = b->Genre;
	a->Time = b->Time;

	b->Song_name = tempTitle;
	b->Artist_name = tempArtist;
	b->Genre = tempGenre;
	b->Time = tempDuration;
}
void playlist::shuffle()
{
	if (!head)
	{
		cout << "The list is EMPTY!";
		return;
	}
	int n = 0;
	songsNode* current = head;
	while (current) 
	{
		n++;
		current = current->next_song;
	}
	for (int i = 0; i < n; i++) 
	{
		//rand function we calculate random number %(residuum) of n
		int random1 = rand() % n;
		int random2 = rand() % n;

		songsNode* song1 = head;
		for (int j = 0; j < random1; j++) 
		{
			song1 = song1->next_song;
		}

		songsNode* song2 = head;
		for (int j = 0; j < random2; j++) 
		{
			song2 = song2->next_song;
		}
		swap(song1, song2);
	}
	cout << "shuffle" << endl;
}
//move down 1 by 1 with this function
void playlist::moveDown(const string& name) 
{
	cout << "Move Down" << endl;
	if (!head) 
	{
		cout << "The playlist is empty." << endl;
		return;
	}
	songsNode* current = head;
	while (current && current->Song_name != name)
	{
		current = current->next_song;
	}
	if (current && current->next_song) 
	{
		swap(current, current->next_song);
	}
}
void playlist::moveUp(const string& name)
{
	cout << "Move Up" << endl;
	if (!head) 
	{
		cout << "The playlist is empty." << endl;
		return;
	}

	songsNode* current = tail;
	while (current && current->Song_name != name) 
	{
		current = current->previous_song;
	}

	if (current && current->previous_song) 
	{
		swap(current, current->previous_song);
	}
}
//display the list
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
		cout << "Name: " << current->Song_name << " "
			<< "Artist: " << current->Artist_name << " "
			<< "Genre: " << current->Genre  << " "
			<< "Time: " << current->Time <<"seconds"<<endl;
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
	playlist.addSong("Je", "Zoz", 219, "jazz");
	playlist.display();
	playlist.moveDown("Dream");
	playlist.display();
	playlist.moveUp("Mirror");
	playlist.display();
	playlist.searchSongByName("Symphony");
	playlist.search("Lil Wayne");
	playlist.display();
	playlist.shuffle();
	playlist.display();
	playlist.removeSongByName("Mirror");
	playlist.display();
	playlist.remove("classic","G");
	playlist.display();
	//playlist.remove("Imagine Dragons","A");
	//playlist.display();
}