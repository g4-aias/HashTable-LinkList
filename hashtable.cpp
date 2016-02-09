#include "hashtable.h"


// constructor
HashTable::HashTable()
{
	size = 0;
	maxsize = 101;
	table = new LinkedList[maxsize];
}

// parameterized constructor
HashTable::HashTable(int n)
{
	size = 0;
	maxsize = SmallestPrime(n);
	table = new LinkedList[maxsize];
}

HashTable::HashTable(const HashTable& sourceht)
{
	// make a new array of size sourceht,
	size = 0;
	maxsize = sourceht.maxsize;
	table = new LinkedList[maxsize];

	vector<string> v1;
	int loc = 0;

	for (int i = 0; i < maxsize; i++)
	{
		v1 = sourceht.table[i].Dump(); // go through each of the sourceht linkedlists, make them into vectors

		if (sourceht.table[i].Size() > 0) // access only valid linkedlists
		{
			for (int j = 0; j <= v1.size()-1; j++)
			{
				loc = (v1.size()-1) - j;
				table[i].Insert(v1.at(loc));
				size++;
			}
		}
	}
}

// destructor
HashTable::~HashTable()
{
	for (int i = 0; i < MaxSize(); i++)
	{
		if (table[i].Size() > 0)
		{
			table[i].RemoveAll();
		}
	}

	delete[] table;
}

// overloaded asignment operator
HashTable& HashTable::operator=(const HashTable& sourceht)
{
	if (this == &sourceht)
		return *this;
	else
	{
		// remove all linkedlists in calling object first
		for (int i = 0; i < this->MaxSize(); i++)
		{
			if (this->table[i].Size() > 0)
			{
				this->table[i].RemoveAll();
			}
		}

		delete[] this->table;

		// apply copy constructor code
		this->size = 0;
		this->maxsize = sourceht.maxsize;
		this->table = new LinkedList[maxsize];

		vector<string> v1;
		int loc = 0;

		for (int i = 0; i < this->maxsize; i++)
		{
			v1 = sourceht.table[i].Dump(); // go through each of the sourceht linkedlists, make them into vectors

			if (sourceht.table[i].Size() > 0) // access only valid linkedlists
			{
				for (int j = 0; j <= v1.size()-1; j++)
				{
					loc = (v1.size()-1) - j;
					this->table[i].Insert(v1.at(loc));
					this->size++;
				}
			}
		}
	}

	return *this;
}

// helper function to find next prime number
int HashTable::SmallestPrime(int n) const
{
	int m = (n*2) + 1;

	while(true)
	{
		if(IsPrime(m) == true)
			break;
		m = m + 2;
	}

	return m;
}

// helper function prime checker
bool HashTable::IsPrime(int n) const
{
	if(n <= 1)
		return false;
	else if (n <= 3)
		return true;
	else if (n%2 == 0 || n%3 == 0)
		return false;

	// start at i=5, 5 is the smallest prime at this point
	// only check to sqrt(n) because of the repeating property
	for (int i = 5; i < floor(sqrt(n)); i+=2 )
	{
		if (n%i == 0)
			return false;
	}

	return true;
}


bool HashTable::Insert(string value)
{
	int key;

	if (Search(value) == true)
		return false;
	else
	{
		key = Hash(value);
		table[key].Insert(value);
	}

	size++;
	return true;
}

bool HashTable::Remove(string value)
{
	int key;

	if (Search(value) == false)
		return false;
	else
	{
		key = Hash(value);
		table[key].Remove(value);
	}

	size--;
	return true;
}

// helper hash function
int HashTable::Hash(string input) const
{
	int key = 0;
	int first = 0;

	for (int i = 0 ; i < input.size(); i++)
	{
		input[i] = input[i] - 96; // this will make a = 1, b = 2, c = 3, ect...

		if (first == 0)
		{
			key = (key * 32) + input[i];
			first++;
		}	
		else
			key = ((key*32) + input[i]) % MaxSize();
	}

	return key;
}


bool HashTable::Search(string value) const
{
	int key = Hash(value);

	if (table[key].Contains(value) == true)
		return true;

	return false;
}

int HashTable::Size() const
{
	return size;
}

int HashTable::MaxSize() const
{
	return maxsize;
}

double HashTable::LoadFactor() const
{
	double loadfac = 0;
	double s = (double)Size();
	double m = (double)MaxSize();
	loadfac = s / m;

	return loadfac;
}

bool HashTable::Resize(unsigned int n)
{
	if (n < MaxSize())
		return false;
	else
	{
		vector<string> v1;
		int loc = 0;
		int key = 0;
		int oldsize = MaxSize();

		// size = to the smallest prime number larger than n
		if (n%2 == 0) 
			maxsize = SmallestPrime(n/2); 
		else
			maxsize = SmallestPrime((n+1)/2);

		LinkedList* tableTemp = new LinkedList[maxsize]; // create a new expanded hashtable

		for (int i = 0; i < oldsize; i++)
		{
			if (table[i].Size() > 0) // makes sure that we are accessing a linkedlist of size > 0
			{
				v1 = table[i].Dump();

				for (int j = 0; j <= v1.size()-1; j++)
				{
					loc = (v1.size()-1) - j;
					key = Hash(v1.at(loc));
					tableTemp[key].Insert(v1.at(loc));
				}
			}

			table[i].RemoveAll();
		}

		delete[] table;
		table = tableTemp;
	}

	return true;
}